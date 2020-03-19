#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
#pragma pack(2)
#define FOR(it,begin,end) for(int it=begin; it<end; it++)
#define BM 0x4d42
typedef unsigned char BYTE; // 1个字节
typedef unsigned short WORD; // 2个字节
typedef unsigned int DWORD; // 4个字节
typedef long LONG;
// 接下来的几个数据结构都是作业说明中所给。
typedef struct tagBITMAPFILEHEADER {
    WORD bfType; // 位图文件的类型，必须为“BM”
    DWORD bfSize; // 位图文件的大小，以字节为单位
    WORD bfReserved1; // 位图文件保留字，必须为0
    WORD bfReserved2; // 位图文件保留字，必须为0
    DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADER; //该结构占据14-2=12个字节。
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize; // 本结构所占用字节数
    LONG biWidth; // 位图的宽度，以像素为单位
    LONG biHeight; // 位图的高度，以像素为单位
    WORD biPlanes; // 目标设备的平面数不清，必须为1
    WORD biBitCount; // 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一
    DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
    DWORD biSizeImage; // 位图的大小，以字节为单位
    LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数
    LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数
    DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数
    DWORD biClrImportant;// 位图显示过程中重要的颜色数
} BITMAPINFOHEADER; //该结构占据40个字节。
typedef struct tagPIXEL24 {
    BYTE b, g, r;
} PIXEL_24;
typedef struct tagPIXEL32 {
    BYTE a, b, g, r;
} PIXEL_32;

BITMAPFILEHEADER bmpHeader;
BITMAPINFOHEADER bmpInfo;
#define MAX_LEN 2000
PIXEL_24 bitmap_24[MAX_LEN][MAX_LEN];
PIXEL_32 bitmap_32[MAX_LEN][MAX_LEN];

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    ifstream fin(argv[1], ios::in | ios::binary);
    ofstream fout(argv[2], ios::out | ios::binary);
    fin.read((char*)&bmpHeader, sizeof(bmpHeader));
    fin.read((char*)&bmpInfo, sizeof(bmpInfo));
    int height = bmpInfo.biHeight, width = bmpInfo.biWidth;
    if(height >= MAX_LEN || width >= MAX_LEN) {
        cout << "[ERROR] The file is too large.\n";
    }
    if(bmpInfo.biBitCount == 24) { // 24位BMP
        FOR(i,0,height) {
            FOR(j,0,width)
                fin.read((char*)&bitmap_24[i][j], sizeof(bitmap_24[i][j]));
            int makeupCnt = (width * 3 + 3) / 4 * 4 - width * 3; // 后端补0的个数
            BYTE makeupCell;
            FOR(k,0,makeupCnt)
                fin.read((char*)&makeupCell, sizeof(makeupCell));
        }
        bmpInfo.biHeight = width, bmpInfo.biWidth = height; // 转置
        fout.write((char*)&bmpHeader, sizeof(bmpHeader));
        fout.write((char*)&bmpInfo, sizeof(bmpInfo));
        for(int i = width-1; i>=0; i--) {
            FOR(j,0,height)
                fout.write((char*)&bitmap_24[j][i], sizeof(bitmap_24[j][i]));
            int makeupCnt = (height * 3 + 3) / 4 * 4 - height * 3;
            BYTE makeupCell = 0;
            FOR(k,0,makeupCnt)
                fout.write((char*)&makeupCell, sizeof(makeupCell));
        }
    } else if(bmpInfo.biBitCount == 32) {
        char rest[84]; // 除去多出来的84字节
        fin.read((char*)rest, 84);
        FOR(i,0,height)
            FOR(j,0,width)
                fin.read((char*)&bitmap_32[i][j], sizeof(bitmap_32[i][j]));
        // 因为都是4的倍数，所以不需要后端补0
        bmpInfo.biHeight = width, bmpInfo.biWidth = height; // 转置
        fout.write((char*)&bmpHeader, sizeof(bmpHeader));
        fout.write((char*)&bmpInfo, sizeof(bmpInfo));
        fout.write((char*)rest, 84);
        for(int i = width-1; i>=0; i--) {
            FOR(j,0,height)
                fout.write((char*)&bitmap_32[j][i], sizeof(bitmap_32[j][i]));
        }
    } else {
        cout << "[ERROR] Please input 24 / 32 -bit BMP.\n";
    }
    fin.close();
    fout.close();
    return 0;
}