#ifndef K_MEANS_THREE_PARAMATER_H
#define K_MEANS_THREE_PARAMATER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include "parameter.h"
#include "FileManager.h"


using namespace std;

enum
{
	a1 = 0,
	a2,
	w
};

class Kmeans
{
public:
	Kmeans(void);
	void Clustering(void);				//�N���X�^�����O
	void GetCenterPos(int c[CLUSTER_NUM][PARAMETER_NUM]);			//�N���X�^�̒��S�_�̃p�����[�^���擾
	void GetCluster(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum);
	void Init(void);
	void ChangePos(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum);
	void ChangeCenterPoint(int CenterPointNum,int clusterNum);

private:
	int GetRandom(int min, int max);	//�����𐶐�				//������
	void DataInit(void);				//�p�����[�^������
	void RandomClusterInit(void);		//�N���X�^������
	void CenterInit(void);				//�N���X�^���S�_��ݒ�
	void Distance(void);				//�������v�Z
	void GetCenter(void);				//���S�_���擾
	void ChangeCluster(void);			//�N���X�^��؂�ւ�
	void DisplayClusters(void);			//���������N���X�^�[��\��
	void DisplayParameter(void);
	void SaveParameter(void);
	bool LoadFile(void);
	bool LoadInitFile(void);
	
//	static bool InitFlg;				//���������
	double pos[RANDOM_MAX][PARAMETER_NUM];		//�p�����[�^
	int center[CLUSTER_NUM];		//�N���X�^��ۑ�
	int cluster[CLUSTER_NUM][CLUST_PARAM_NUM];
	double individual[RANDOM_MAX][PARAMETER_NUM];			//
	double distance[CLUSTER_NUM][RANDOM_MAX];	//
	double centerpoint[CLUSTER_NUM][PARAMETER_NUM];			//���S�_
	double count_Group[CLUSTER_NUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//�J�Ԃ��p�t���O
	FileManager fmp;						//�ė��p�ړI�f�[�^
	ofstream ofs;

};

#endif //K_MEANS_THREE_PARAMATER_H