#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

struct AlignmentEntry {
    const char *name;
    Elf32_Word alignment;
};

struct AlignmentEntry alignment_entries[] = {
    { ".text",   0x8 },
    { ".data",   0x8 },
    { ".rodata", 0x8 },
    { ".sdata",  0x4 },
    { ".sbss",   0x4 },
    { ".bss",    0x8 }
};

int main(int argc, const char *argv[]) {
    // Check args
    if (argc < 2) {
        printf("elf_patcher: input file not specified\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "rb+");
    if (file == NULL) {
        printf("elf_patcher: could not open input file\n");
        return 1;
    }

    // Read ehdr
    Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));
    fread(ehdr, sizeof(Elf32_Ehdr), 1, file);

    // Read shdrs
    size_t section_headers_size = ehdr->e_shentsize * ehdr->e_shnum;
    Elf32_Shdr *shdr = malloc(section_headers_size);
    fseek(file, ehdr->e_shoff, SEEK_SET);
    fread(shdr, section_headers_size, 1, file);

    // Read string table
    Elf32_Shdr *string_tbl_shdr = &shdr[ehdr->e_shstrndx];
    char *string_tbl = malloc(string_tbl_shdr->sh_size);
    fseek(file, string_tbl_shdr->sh_offset, SEEK_SET);
    fread(string_tbl, string_tbl_shdr->sh_size, 1, file);

    // Read sections
    for (int i = 0; i < ehdr->e_shnum; i++) {
        Elf32_Shdr *section_header = &shdr[i];
        for (int s = 0; s < sizeof(alignment_entries) / sizeof(alignment_entries[0]); s++) {
            if (strcmp(&string_tbl[section_header->sh_name], alignment_entries[s].name) == 0) {
                section_header->sh_addralign = alignment_entries[s].alignment;
                break;
            }
        }
    }

    // Write back to file
    fseek(file, ehdr->e_shoff, SEEK_SET);
    fwrite(shdr, section_headers_size, 1, file);

    // Cleanup
    fclose(file);
    return 0;
}