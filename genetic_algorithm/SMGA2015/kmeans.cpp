#include <math.h>
#include "kmeans.h"

Kmeans::Kmeans(void)
{
}

/*!
 * @brief ������
 *
 * @param[in] data_no �f�[�^�̐�
 * @param[in] cluster_no �N���X�^�̐�
 * @param[in] parameter_no �p�����[�^�̐�
 *
 */
void Kmeans::Init(int data_no, int cluseter_no, int parameter_no)
{
	this->data_no = data_no;
	this->cluster_no = cluseter_no;
	this->parameter_no = parameter_no;

	data.resize(data_no * parameter_no, 0);
	id.resize(data_no, 0);
	center2.resize(cluster_no * parameter_no, 0);
}

/*!
 * @brief �f�[�^�̃Z�b�g
 * @return true:�����Cfalse:���s
 */
bool Kmeans::SetData(vector<double> data){
	if (data.size() != data_no * parameter_no){
		cout << "SetData: check the number of data\n" << endl;
		return false;
	}
	this->data = data;
	for(int i = 0; i < data_no; i ++){
		id[i] = rand() % cluster_no;
	}
	calcCenter();
	return true;
}

void Kmeans::calcCenter()
{
	vector<double> center_t(cluster_no * parameter_no, 0.0);
	vector<int> num(cluster_no, 0);

	for(int i = 0; i < data_no; i++){
		vector<double> pickup_data = GetVector(data, i);
 		int cluster = id[i];

		num[cluster] ++;
		for(int j = 0;j < parameter_no; j ++){
			center_t[parameter_no * cluster + j] += pickup_data[j];
		}
    }
	for(int i = 0; i < cluster_no; i ++){
		for(int j = 0; j < parameter_no; j ++){
			center_t[parameter_no * i + j] /= num[i];
		}
	}
	copy(center_t.begin(), center_t.end(), center2.begin());
}

/*!
 * @brief �����̎擾
 * @param[in] a �ʒu�x�N�g��
 * @param[in] b �ʒu�x�N�g��
 * @return ����
 */
double Kmeans::GetDistance(vector<double>a, vector<double>b)
{
	if (a.size() != b.size()) return 0.0;
	
	int dim = a.size();
	double val = 0.0;
	for(int i = 0; i < dim; i ++){
		val += fabs(a[i] - b[i]);
	}
	return pow(val, 1.0/dim);
}

/*!
 * @brief �̂̃f�[�^���擾����
 * @param[in] id ID�ԍ� (0 - (data_no-1))
 * @return �ʒu�x�N�g��
 */
vector<double> Kmeans::GetVector(vector<double> a, int id){
	vector<double> ret(parameter_no);
	for(int i = 0; i < parameter_no; i ++){
		ret[i] = a[id * parameter_no + i];
	}
	return ret;
}

/*
 * @brief K-means�̌J��Ԃ�������
 * ���X�ɏd�S�Ƒ�����̂��v�Z���Ă���
 */
void Kmeans::ReClustering(void)
{
	for(int i = 0; i < data_no; i++){
		vector<double> pickup_data = GetVector(data, i);
		double min = GetDistance(pickup_data, GetVector(center2, 0));
        int min_j = 0;
 
		for(int j = 1; j < cluster_no; j++){
			double dist = GetDistance(pickup_data, GetVector(center2, j));
			if(min > dist){
				min   = dist;
				min_j = j;
			}
        }
		id[i] = min_j;
    }
	calcCenter();
}


void Kmeans::Clustering(void)
{
	vector<double> pre_center(cluster_no * parameter_no, 0);
	double distance = 1.0;
	for(int n = 0; (n < 100)&&(distance != 0.0); n ++)
	{
		copy(center2.begin(), center2.end(), pre_center.begin());
		ReClustering();
		distance = 0.0;
		for(int i = 0; i < parameter_no; i ++){
			distance += GetDistance(center2, pre_center);
		}
	}
}

/*!
 * @brief �N���X�^�ɑ�����f�[�^���擾
 * 
 * @param[out] c �N���X�^�ɑ�����f�[�^�̔ԍ�
 * @param[in] clusterNum �N���X�^�̔ԍ�
 *
 * @return �N���X�^�ɑ�����f�[�^�̐�
 */
int Kmeans::GetCluster(vector<int> *c, int clusterNum)
{
	c->clear();
	for(int i = 0; i < data_no; i++)
	{
		if (id[i] == clusterNum){
			c->push_back(i);
		}
	}
	return c->size();
}

/*
 * @brief �N���X�^���̕\��
 */
ostream &operator<<(ostream &out, const Kmeans &kmeans)
{
	for(int i = 0; i < kmeans.cluster_no; i++)
	{
		out << "Disp Cluster Num:" << i + 1 << endl;
		out << "Center Point " ;

		for(int j = 0; j < kmeans.parameter_no; j++)
		{
			out << ",";
			out << " " << (int)kmeans.center2[kmeans.parameter_no * i + j] << " ";
		}
		out << endl << endl;
		for(int j = 0; j < kmeans.data_no; j++)
		{
			if (kmeans.id[j] == i){
				out << "No." << j+1 << " ";
				for(int k = 0; k < kmeans.parameter_no; k++)
				{
					out << "," << (int)kmeans.data[kmeans.parameter_no * j + k];
				}
				out << endl;
			}
		}
		out << endl;
	}
	out << endl;

	return out;
}
