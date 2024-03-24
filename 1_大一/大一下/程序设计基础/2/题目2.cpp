#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���ͼƬ����ɫ��������RGB
char src1[1000][1000][3];
char src2[1000][1000][3];
char dst[1000][1000][3];

//λͼ�ļ�ͷ
struct bfHead
{
    char bfType[2]; //��������ļ��Ƿ���"BM"����
	long bfSize;
	long bfReserved;
	long bfOffBits;
};

//λͼ��Ϣͷ
struct biHead
{
	long biSize;
	long biWidth;   //ͼ�Ŀ��
	long biHeight;  //ͼ�ĸ߶�
	short biPlanes;
	short biBitCount;   //���ص�λ��ȣ�24��Ϊ24λ���ͼ
	long biCompression;
	long biSizeImage;
	long biXPelsPerMeter;
	long biYpelsPerMeter;
	long biClrUsed;
	long biClrImportant;
};

int main(int argc, char* argv[])
{
    struct bfHead bfSrc1, bfSrc2;
    struct biHead biSrc1, biSrc2;

    //��2��ԭʼ�ļ� ����ȡ����
    FILE *fp1 = fopen(argv[1], "r+b");
    FILE *fp2 = fopen(argv[3], "r+b");

    //��ϵİٷֱȣ��������� 80% ��percentΪ0.8
    double percent = 0;
    for (int i = 0; i < strlen(argv[2]) - 1; ++i)
        percent = percent * 10 + (argv[2][i] - '0');
    percent /= 100;

    //��Ŀ���ļ� ��д������
    //����ļ�������û�еģ�fopen�ᴴ��һ���µ��ļ���������ļ��Ѿ����ڣ�fopen�Ὣ�串�ǵ�
    FILE *fp3 = fopen(argv[4], "w+b");

    //��ȡλͼ�ļ�ͷ λͼ��Ϣͷ
    fread(&bfSrc1, 14, 1, fp1);
    fread(&bfSrc2, 14, 1, fp2);
    fread(&biSrc1, 40, 1, fp1);
    fread(&biSrc2, 40, 1, fp2);

    //����Ƿ�ΪBM���� �Ƿ�Ϊ24λ���ͼ ��Ƭ�ߴ��Ƿ����
    if (bfSrc1.bfType[0]=='B'&& bfSrc1.bfType[1]=='M' && bfSrc2.bfType[0]=='B' && bfSrc2.bfType[1]=='M'
        && biSrc1.biBitCount == 24 && biSrc2.biBitCount == 24
        && biSrc1.biWidth == biSrc2.biWidth && biSrc1.biHeight == biSrc2.biHeight)
    {
        //��ȡ��ɫ��������
        //������ ��������
        for (int y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            //������ ��ǰ���
            for (int x = 0; x < biSrc1.biWidth; ++x)
            {
                //�ļ��������а���BGR��˳��洢��������RGB��˳��洢
                for (int k = 2; k >= 0; --k)
                {
                    fread(&src1[x][y][k], 1, 1, fp1);
                    fread(&src2[x][y][k], 1, 1, fp2);
                }
            }
        }

        //������ص�Ŀ���ļ�����
        for (int y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            for (int x = 0; x<biSrc1.biWidth; ++x)
            {
                for (int k = 2; k >= 0; --k)
                    dst[x][y][k] = src1[x][y][k] * percent + src2[x][y][k] * (1 - percent);
            }
        }

        //дĿ���ļ�
        fwrite(&bfSrc1,14,1,fp3);
        fwrite(&biSrc1,40,1,fp3);
        for (int y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            for (int x = 0; x<biSrc1.biWidth; ++x)
            {
                for (int k = 2; k >= 0; --k)
                    fwrite(&dst[x][y][k], 1, 1, fp3);
            }
        }

        printf("ִ�гɹ�\n");
    }

    //�ر��ļ�
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

