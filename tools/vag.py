from dataclasses import dataclass

@dataclass
class Vag:
    splt: int
    prog: int
    bank: int
    grp: int
    unk: int
    flag: int
    bendh: int
    bendl: int

    def macro(self) -> str:
        return f"KL2_VAG({self.splt}, {self.prog}, {self.bank}, {self.grp}, {self.unk}, 0x{self.flag:02X}, {self.bendh}, {self.bendl})"
    
    def id(self) -> int:
        vag_id = self.splt & 0xFF
        vag_id |= (self.prog & 0x7F) << 8
        vag_id |= (self.bank & 1) << 15
        vag_id |= (self.grp & 0xF) << 16
        vag_id |= (self.unk & 0xF) << 20
        vag_id |= (self.flag & 0xFF) << 24
        vag_id |= (self.bendh & 0xFFF) << 32
        vag_id |= (self.bendl & 0xFFF) << 44
        return vag_id

# From hoshino/h_gamesnd.c
def decode_vag(id: int) -> Vag:
    splt = id & 0xFF
    prog = (id >> 8) & 0x7F
    bank = (id >> 15) & 1
    grp = (id >> 16) & 0xF
    unk = (id >> 20) & 0xF
    flag = (id >> 24) & 0xFF
    bendh = (id >> 32) & 0xFFF
    bendl = (id >> 44) & 0xFFF
    return Vag(splt, prog, bank, grp, unk, flag, bendh, bendl)

if __name__ == "__main__":
    while True:
        inp = input("Enter VAG ID: ")
        if not inp:
            break
        vag_id = int(inp[2:], base=16) if inp.startswith("0x") else int(inp, base=10)
        vag = decode_vag(vag_id)
        assert(vag_id == vag.id())
        print(vag.macro())
