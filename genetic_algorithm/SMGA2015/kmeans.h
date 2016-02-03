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
	int ClusterParameter[CLUSTER_NUM];

private:
	ofstream ofs;

public:
	Kmeans(void);
	void Init(int data_no, int cluseter_no, int parameter_no);
	bool SetData(vector<double> data);
	void Clustering(void);				//�N���X�^�����O
	void GetCluster(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);
	friend ostream &operator<<(ostream &out, const Kmeans &kmeans);

private:
	void calcCenter();
	void ReClustering(void);				//���S�_���擾
	double GetDistance(vector<double>a, vector<double>b);	//�������v�Z
	vector<double> GetVector(vector<double> a, int id);
	void DisplayClusters(void);			//���������N���X�^�[��\��

	int data_no;				// �f�[�^�� 
	int cluster_no;				// �N���X�^��
	int parameter_no;			// �p�����[�^���i�����j
	vector<double> data;		// �f�[�^(double�^�Ƃ���)
	vector<double> id;			// �f�[�^��������N���X�^�ԍ�
	vector<double> center2;		// �d�S�̒l
};

#endif //K_MEANS_H