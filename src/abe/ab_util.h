#ifndef __AB_UTIL_H
#define __AB_UTIL_H

#include "common.h"
#include "nakano/main.h"

#ifdef __cplusplus

template <typename T>
class CVector {
public:
	union {
        T x;
        T r;
        T s;
        T u;
    };

	union{
        T y;
        T g;
        T t;
        T v;
    };

	union {
        T z;
        T b;
        T q;
    };

	union {
        f32 w;
        f32 a;
    };
	
	CVector<T>& operator=(CVector &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

	CVector() {
        x = T();
        y = T();
        z = T();
        w = T();
    }

	CVector(T v0) {
        x = v0;
        y = T();
        z = T();
        w = T();
    }

	CVector(T v0, T v1) {
        x = v0;
        y = v1;
        z = T();
        w = T();
    }

	CVector(T v0, T v1, T v2) {
        x = v0;
        y = v1;
        z = v2;
        w = T();
    }

	CVector(T v0, T v1, T v2, T v3) {
        x = v0;
        y = v1;
        z = v2;
        w = v3;
    }

	CVector<T>& Set(T v0, T v1, T v2, T v3) {
        x = v0;
        y = v1;
        z = v2;
        w = v3;
    }

	T& operator[](s32 index) {
        return ((T *)&this)[index];
    }

	operator T *() {
        return &x; // ?
    }
}  __attribute__((aligned(16)));

template <typename T>
class CMatrix { // 0x40
private:
    /* 0x00 */ CVector<T> m_matrix[4];
    
public:
    // CMatrix<T>& operator=();
    // CMatrix();
    // CMatrix();

    CVector<T>& operator[](s32 index) {
        return m_matrix[index];
    }

    operator CVector<T> *() {
        return &m_matrix[0]; // ?
    }

    // operator T (*)[3]() {
    //     return &m_matrix[0]; // ?
    // }
};

typedef CVector<s32> CIVector;
typedef CVector<f32> CFVector;
typedef CMatrix<f32> CFMatrix;

class SPAD_TYPE { // 0x180
	/* 0x000 */ CFVector vf0;
	/* 0x010 */ CFVector vf1;
	/* 0x020 */ CFVector vf2;
	/* 0x030 */ CFVector vf3;
	/* 0x040 */ CIVector vi0;
	/* 0x050 */ CIVector vi1;
	/* 0x060 */ CIVector vi2;
	/* 0x070 */ CIVector vi3;
	/* 0x080 */ CFMatrix lsm;
	/* 0x0c0 */ CFMatrix lsm2;
	/* 0x100 */ CFMatrix lsm3;
	/* 0x140 */ CFMatrix mat;
};

union CData { // 0x10
    /* 0x0 */ u128 u_128;
    /* 0x0 */ u64 u_64[2];
    /* 0x0 */ u32 u_32[4];
    /* 0x0 */ struct { // 0x10
        /* 0x0 */ union { // 0x4
            /* 0x0 */ s32 x;
            /* 0x0 */ s32 r;
            /* 0x0 */ s32 u;
            /* 0x0 */ f32 s;
        };
        /* 0x4 */ union { // 0x4
            /* 0x4 */ s32 y;
            /* 0x4 */ s32 g;
            /* 0x4 */ s32 v;
            /* 0x4 */ f32 t;
        };
        /* 0x8 */ union { // 0x4
            /* 0x8 */ s32 z;
            /* 0x8 */ s32 b;
            /* 0x8 */ f32 q;
        };
        /* 0xc */ union { // 0x4
            /* 0xc */ s32 w;
            /* 0xc */ s32 a;
        };
    } pack;
};

class CGifPacket { // 0x10
    /* 0x0 */ CData *m_buf;
    /* 0x4 */ CData *m_end;
    /* 0x8 */ CData *m_giftag0;
    /* 0xc */ CData *m_giftag1;
    
    // CGifPacket& operator=();
    // CGifPacket();
    // CGifPacket();

    void Init(void *addr) {
        this->m_buf = (CData *)addr; // Line 105
        this->m_end = this->m_buf + 1; // Line 106
        this->m_giftag0 = this->m_buf + 2; // Line 107
        this->m_giftag1 = this->m_buf + 2; // Line 108
    }

    // void Terminate();
    // void Terminate();

    void SendFromSPAD() { // Line 171
        this->m_buf->u_128 = 0;
        this->m_buf->u_32[0] = (u32)SPR_MEM_IDX(this->m_end - this->m_buf);
        if (this->m_end - this->m_buf > 2) {
            FlushCache(WRITEBACK_DCACHE);
            DmaChGIF->chcr.TTE = 1;
            void *addr = this->Buffer();
            sceDmaSend(DmaChGIF, addr);
        }
    }

    void Add(u64 addr, u64 data) {
        this->m_end->u_64[0] = data;
        this->m_end->u_64[1] = addr;
        this->m_end++; // ?
    }

    // void Cancel();

    CData* Buffer() {
        return (CData *)SPR_SRC(this->m_buf);
        // return m_end; // ?
    }
};

struct CObject { // 0x2
protected:
    /* 0x0 */ u16 m_stat0;
    
public:
    // CObject& operator=();
    // CObject();
    // CObject();
    void OnCreate();
    bool IsReserved();
    void Reserve();
    void Delete();
};

struct CPrimitive { // 0x1
	static s32 TERMINATE_SIZE;
	
	// CPrimitive& operator=();
	// CPrimitive();
	// CPrimitive();
	void Open();
	void Terminate();
};

struct CBillBoard : /* 0x00 */ CPrimitive { // 0xb0
	static s32 N_VERTEX;
	static s32 PACKET_SIZE;
	/* 0x10 */ CFVector m_point[4];
	/* 0x50 */ CFVector m_texel[4];
	/* 0x90 */ u64 m_tex0;
	/* 0x98 */ u64 m_clamp;
	/* 0xa0 */ s16 m_texid;
	
	// CBillBoard& operator=();
	// CBillBoard();
	// CBillBoard();
	// void Init();
	// bool MakePacket();
	// bool MakePacketP();
	// bool MakePacket();
	// bool MakePacket();
	// bool MakePacketP();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

extern s32 MfifoOn;

#ifdef __cplusplus
}
#endif

#endif