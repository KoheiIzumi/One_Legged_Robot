#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "parameter.h"
#include "Utility.h"
#include "Serial.h"
#include "kmeansfiveparamater.h"
#include "FileManager.h"

class GA
{
public:
	void Initialize();
	void Selection(int c);
	void Crossover();
	void Mutation();
	void MakeSring();
	void RobotMove();
	void DisplayEvaluatedValue();
	void Clustering(void);
	void InitEvalValue(void);
	void GAProcessing(void);

private:
	Utility utility;
	Serial serial;
	Kmeans kmeans;
	int angle[CLUST_PARAM_NUM][PARAMETER_NUM];
	int result[CLUST_PARAM_NUM][2];
	std::string str[CLUST_PARAM_NUM];
	int move_result[CLUST_PARAM_NUM];
	std::bitset<32> parent[CLUST_PARAM_NUM][PARAMETER_NUM];
	std::bitset<32> child[CLUST_PARAM_NUM][PARAMETER_NUM];
	int EvalValue[CLUSTER_NUM];
	FileManager fm;
	FileManager fmc1;
	FileManager fmc2;
	FileManager fmc3;

	void ResetStr();
};
#endif