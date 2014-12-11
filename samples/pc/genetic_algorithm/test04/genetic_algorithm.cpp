#pragma warning(disable: 4819)

#include <iostream>
#include <fstream>
#include <bitset>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "parameter.h" 
#include "individualData.h"

int count =0;
int count2 =0;
double	centralPoint[10];		// �N���X�^�Z���g�����|�C���g���W
int		population[10];		// �N���X�^�ɑ�����̐�
individualData inv[RANDOM_MAX];
individualData invAll[RANDOM_MAX];

unsigned long long GetTimeStamp()
{
	//���ݎ�����TimeStamp�擾
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	// 1970/1/1 ����̍������擾
	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	// ������b�ŕ\��
	return diff.total_microseconds();
}

std::string GetTimeISOString()
{
	//get current time to milliseconds
	boost::posix_time::ptime today = boost::posix_time::second_clock::local_time();

	return boost::posix_time::to_iso_string(today);
}

void Random(int min, int max, int result[RANDOM_MAX])
{
	//��������
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);//�������z

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}
}

int Random(int min, int max)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);
	//sleep for milliseconds
	boost::this_thread::sleep(boost::posix_time::microseconds(1000));
	
	return dist(gen);
}

void Initialize(int angle[])
{
	Random(0, 180, angle);
}

void initCentralPoint()
{
	for(int i=0;i<10;i++){
		centralPoint[i]=-180 + (double)(2*180)/10 * i;
	}
}

void clustering(int angle[])
{
	
	// ����
	int dist[2]={0,0};
	//�̂��N���X�^�ɕ���

	for(int loop=0;loop<5;loop++){
		// �e�̂ɑ΂���
		for(int i=0;i<RANDOM_MAX;i++){
			dist[1]=180;//sin��cos�̊p�x
			// �e�N���X�^�ɑ΂���
			for(int j=0;j<10;j++){
				// �̂ƃN���X�^�̊���Ƃ̋������v�Z
				dist[0]=fabs(centralPoint[j] - inv[i].getGene()); //fabs��Βl��\��
				// ���܂ň�ԋ߂������N���X�^��苗�����߂�������
				if(dist[0]<dist[1]){//range�͈͈̔ȊO�̓N���X�^�ɐݒ肵�Ȃ�
					// ���݂̌̂����̃N���X�^�ɐݒ�
					inv[i].setCluster(j);
					dist[1]=dist[0];
				}//0�`180�͈̔͂Őݒ�A���S�_��
			}
		}
	}
	//�N���X�^���Ƃ̌̐����v�Z
	for(int i=0;i<10;i++) population[i]=0;				//������
	for(int i=0;i<10;i++)  population[inv[i].getCluster()]++;


	//�N���X�^�̃Z���^�[�|�C���g���v�Z
	double sum[10];
	for(int i=0;i<10;i++) sum[i]=0;						//������	

	// �N���X�^���Ƃ̑S�ő̂̉���Ԃ̒l�����v
	for(int i=0;i<RANDOM_MAX;i++){
		sum[inv[i].getCluster()] += inv[i].getGene();
	}
	//���ς����
	for(int i=0;i<10;i++){
		if(population[i]!=0){
			sum[i] /= population[i];
			centralPoint[i] = sum[i];
		}
		// �N���X�^�ɑ�����̂������Ȃ����ꍇ
		// �� �V�����N���X�^�������_���ɍ쐬
		else centralPoint[i]=(double)rand()/RAND_MAX *180 -180/2;
	}
}


void Selection(int angle[], int result[][2])
{
	int temp, angle_temp;
	int target_abs[RANDOM_MAX][2];

	individualData swap;
	int F=1;

	//�N���X�^���Ƃɕ��ёւ��� 000,1111,22,333,4444,555,666666,�c
	while(F){
		F=0;
		for(int i=0;i<RANDOM_MAX-1;i++){
			// ���̌̂̃N���X�^�ԍ������A
			// ���݂̌̂̃N���X�^�ԍ��̂ق���������
			if(inv[i].getCluster() > inv[i+1].getCluster() ){
				// �̂̔ԍ������ւ�
				swap		= inv[i];
				inv[i]		= inv[i+1];
				inv[i+1]	= swap;
				
				F=1;
			}
		}
	}

for(int i=0;i<10;i++){
		F=1;
  while(F){
			F=0;

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target_abs[i][0] = std::abs(angle[i] - TARGET_VALUE);
		target_abs[i][1] = i;
	}

	for(int j=0; j<RANDOM_MAX-1; j++)
	{
		for(int k=j+1; k<RANDOM_MAX; k++)
		{
			if(target_abs[j][0] > target_abs[k][0])
			{
				temp = target_abs[j][0];
				angle_temp = target_abs[j][1];
				target_abs[j][0] = target_abs[k][0];
				target_abs[j][1] = target_abs[k][1];
				target_abs[k][0] = temp;
				target_abs[k][1] = angle_temp;
			}
		}
	}

	for(int l=0; l<RANDOM_MAX * RANKING_RATE; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target_abs[l][m];
		}
	}
}
}
}

unsigned long DecimalToBinary(std::bitset<32> decimal)
{
	std::bitset<32> value(decimal);
	
	return value.to_ulong();
}

std::bitset<32> BinaryToDecimal(std::bitset<32> binary)
{
	std::bitset<32> value(binary);

	return value;
}

std::bitset<32> SetMask()
{
	std::bitset<32> mask_bit;
	int bit_counter = 0;

	for(size_t i=0; i<mask_bit.size(); i++)
	{
		if(bit_counter == 0)
		{
			mask_bit.set(i, 1);
			bit_counter = 1;
		}
		else
		{
			bit_counter = 0;
		}
	}

	return mask_bit;
}

std::bitset<32> SetMaskRandom()
{
	std::bitset<32> mask_bit;
	int bit_counter = 0;

	for(size_t i=0; i<mask_bit.size(); i++)
	{
		bit_counter = Random(0, 1);

		if(bit_counter == 0)
		{
			mask_bit.set(i, 1);
		}
	}

	return mask_bit;
}

void Crossover(std::bitset<32> parent[], std::bitset<32> child[])
{
	std::bitset<32> mask = SetMask();
	int counter = 0;
	int pSum=0;

	for(int i=0;i<10;++i){

	for(int i=0; i<RANDOM_MAX; i+=2)
	{	
		counter += 2;
		if(counter == INDIVIDUALS_NUMBER)
		{
			mask = SetMaskRandom();
			counter = 0;
		}

		for(size_t j=0; j<parent[i].size(); j++)
		{
			if(mask.test(j) == 0)
			{
				child[i].set(j, parent[i].test(j));
				child[i+1].set(j, parent[i+1].test(j));
			}
			else
			{
				child[i].set(j, parent[i+1].test(j));
				child[i+1].set(j, parent[i].test(j));
			}
		}
	}
}
}

void Mutation(std::bitset<32> child[])
{
	double random;
	int mutation_pos;
	int pSum=0;

	for(int i=0;i<10;++i){

	for(int i=0; i<RANDOM_MAX; i++)
	{
		random = Random(0, 100) * 0.01;

		if(random <= MUTATION_RATE)
		{
			mutation_pos = Random(0, MUTATION_POS);
			child[i].flip(mutation_pos);
		}
	}
}
}

int main()
{
	int angle[RANDOM_MAX];
	int result[RANDOM_MAX][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX];
	std::bitset<32> child[RANDOM_MAX];

	std::ofstream ofs(GetTimeISOString() + ".csv");
	
	Initialize(angle);

	count=0;
		count2++;
		if(count2>LOOP_COUNT){
			//������
			for(int i=0;i<10;i++)inv[i].setRandom();
			initCentralPoint();
			count2=0;
		}
	
	clustering(angle);

	int F=1;
		
		individualData swap;
		// �\�[�g�ς݂̌̏������ׂăR�s�[
		for(int i=0;i<RANDOM_MAX;i++){
			invAll[i] = inv[i];
		}

		// �N���X�^�Ɋ֌W�Ȃ��K���x���������ɕ��ёւ���
		while(F){
			F=0;
			for(int i=0;i<RANDOM_MAX-1;i++){
				// ���̂�莟�̌̂̕����K���x���������������ւ�
				if(invAll[i].getEva() < invAll[i+1].getEva() ){
					swap = invAll[i];
					invAll[i] = invAll[i+1];
					invAll[i+1] = swap;
					F=1;
				}
			}
		}

	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT:" << i << std::endl;
		ofs << "No." << i+1 << std::endl;

		Selection(angle, result);

		for(int j=0; j<RANDOM_MAX; j++)
		{
			if(parent_cpy == INDIVIDUALS_NUMBER)
			{
				parent_cpy = 0;
			}
			parent[j] = BinaryToDecimal(angle[result[parent_cpy][1]]);
			parent_cpy += 1;
		}

		ofs << "result_angle" << "\t";

		for(int k=0; k<INDIVIDUALS_NUMBER; k++)
		{
			std::cout << "---- No." << k+1 << " -----" << std::endl;
			std::cout << "result_angle:" << angle[result[k][1]] << std::endl;
			ofs << angle[result[k][1]] << "\t";
		}
		ofs << std::endl;
	
		std::cout << "----- Crossover -----" << std::endl;
		Crossover(parent, child);

		ofs << "Crossover" << "\t";

		for(int l=0; l<RANDOM_MAX; l++)
		{
			ofs << DecimalToBinary(child[l]) << "\t";
		}
		ofs << std::endl;

		std::cout << "----- Mutation -----" << std::endl;
		Mutation(child);

		ofs << "Mutation" << "\t";

		for(int l=0; l<RANDOM_MAX; l++)
		{
			angle[l] = DecimalToBinary(child[l]);
			ofs  << angle[l] << "\t";
		}
		ofs << std::endl;
	}

	ofs << "final_result" << "\t";
	Selection(angle, result);
	for(int m=0; m<INDIVIDUALS_NUMBER; m++)
	{
		std::cout << "child[" << m << "]:" << angle[result[m][1]] << std::endl;
		ofs << angle[result[m][1]] << "\t";
	}
	ofs << std::endl;



	return 0;
}
