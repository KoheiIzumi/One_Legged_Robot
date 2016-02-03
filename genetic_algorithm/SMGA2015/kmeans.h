#ifndef K_MEANS__H
#define K_MEANS__H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <vector>
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

//	void ChangePos(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);
//	void ChangeCenterPoint(int CenterPointNum,int clusterNum);
	int ClusterParameter[CLUSTER_NUM];

private:
	bool LoadFile(void);
	bool LoadInitFile(void);
	
//	static bool InitFlg;				//���������
	double pos[RANDOM_MAX][PARAMETER_NUM];		//�p�����[�^
	int center[CLUSTER_NUM];		//�N���X�^��ۑ�
	int cluster[CLUSTER_NUM][RANDOM_MAX];
	double individual[RANDOM_MAX][PARAMETER_NUM];			//
	double distance[CLUSTER_NUM][RANDOM_MAX];	//
	double centerpoint[CLUSTER_NUM][PARAMETER_NUM];			//���S�_
	double count_Group[CLUSTER_NUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//�J�Ԃ��p�t���O
	FileManager fmp;						//�ė��p�ړI�f�[�^
	ofstream ofs;

public:
	Kmeans(void);
	void Init(int data_no, int cluseter_no, int parameter_no);
	bool SetData(vector<double> data);
	void Clustering(void);				//�N���X�^�����O
	void GetCluster(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);

private:
	void ReClustering(void);				//���S�_���擾
	double GetDistance(vector<double>a, vector<double>b);	//�������v�Z
	vector<double> GetVector(vector<double> a, int id);
	void DisplayClusters(void);			//���������N���X�^�[��\��
	void DisplayParameter(void);

	int data_no;				// �f�[�^�� 
	int cluster_no;				// �N���X�^��
	int parameter_no;			// �p�����[�^���i�����j
	vector<double> data;		// �f�[�^(double�^�Ƃ���)
	vector<double> id;			// �f�[�^��������N���X�^�ԍ�
	vector<double> center2;		// �d�S�̒l
};

#endif //K_MEANS_H