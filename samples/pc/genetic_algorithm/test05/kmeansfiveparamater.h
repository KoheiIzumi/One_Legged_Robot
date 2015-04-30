#ifndef K_MEANS_FIVE_PARAMATER_H
#define K_MEANS_FIVE_PARAMATER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>


using namespace std;

#define NUM 100
#define cNUM 3
#define hNUM NUM/cNUM
#define pNUM 5

enum
{
	a1 = 0,
	t1,
	a2,
	t2,
	w
};

class kmeans
{
public:
	kmeans(void);
	void Clustering(void);				//�N���X�^�����O
	void GetCluster(double c[cNUM][pNUM]);			//�N���X�^���擾

private:
	int GetRandom(int min, int max);	//�����𐶐�
	void Init(void);					//������
	void DataInit(void);				//�p�����[�^������
	void RandomClusterInit(void);		//�N���X�^������
	void CenterInit(void);				//�N���X�^���S�_��ݒ�
	void Distance(void);				//�������v�Z
	void GetCenter(void);				//���S�_���擾
	void ChangeCluster(void);			//�N���X�^��؂�ւ�
	
//	static bool InitFlg;				//���������
	double pos[NUM][pNUM];		//�p�����[�^
	int cluster[cNUM];		//�N���X�^��ۑ�
	double individual[NUM][pNUM];			//
	double distance[cNUM][NUM];	//
	double centerpoint[cNUM][pNUM];			//���S�_
	double count_Group[cNUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//�J�Ԃ��p�t���O

};

#endif //K_MEANS_FIVE_PARAMATER_H