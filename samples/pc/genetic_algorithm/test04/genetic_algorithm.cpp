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

unsigned long long GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

std::string GetTimeISOString()
{
	boost::posix_time::ptime today = boost::posix_time::second_clock::local_time();

	return boost::posix_time::to_iso_string(today);
}

void Random(int min, int max, int result[RANDOM_MAX])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}	
}

void CenterRandom(int min, int max, int centerpoint[cNUM])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int j=0; j<cNUM; j++)
	{
		centerpoint[j]=dist(gen);
	}
}

int Random(int min, int max)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	boost::this_thread::sleep(boost::posix_time::microseconds(1000));

	return dist(gen);
}

void Initialize(int angle[])
{
	Random(0, 180, angle);
	
}

void CenterInitialize(int centerpoint[])
{
	CenterRandom(0, 180, centerpoint);
}

void clustering(int angle[], int centerpoint[], int result[][cNUM][2]){
	int distance[RANDOM_MAX][cNUM];
	int min[RANDOM_MAX][cNUM];
	int point_counter[cNUM]={};
	int individualsum[cNUM]={};
	int same_count = 0;
	int cluster_angle[RANDOM_MAX][cNUM]={};
	int w, s; 
	int target[RANDOM_MAX][cNUM][2]={};
	bool loop=true;

	while (loop)
	{
		for(int i=0; i<RANDOM_MAX; i++){
			for(int j=0; j<cNUM; j++){
				distance[i][j]=abs(angle[i]-centerpoint[j]);	
			}
		}

		for(int i=0; i<RANDOM_MAX; i++){
			min[i][0] = distance[i][0];
			min[i][1]=0;
			for(int j=0; j<cNUM; j++){
				if(distance[i][j]<min[i][0]){
					min[i][0]=distance[i][j];
					min[i][1]=j;
				}
			}
		}

		for(int i=0; i<RANDOM_MAX; i++){
			for(int j=0; j<cNUM; j++){
				if(min[i][1]==j){
					individualsum[j] += angle[i];
					point_counter[j]++;
				}
			}
		}

		int same_count = 0;
		for(int i=0;i<cNUM; i++){
			if(point_counter[i] != 0){
				if((individualsum[i] / point_counter[i]) == centerpoint[i])
						same_count ++;
				
				centerpoint[i] = individualsum[i] / point_counter[i];
			}

			if(same_count == cNUM){
				loop=false;
			}
		}
		for(int c=0; c<cNUM; c++){
			for(int i=0; i<RANDOM_MAX; i++){
				if(min[i][1]==c){
					cluster_angle[i][c]=angle[i];
				}
			}
		}		
	}
/*
	for(int i=0; i<RANDOM_MAX; i++){
		for(int j=0; j<cNUM; j++){
			
			target[i][j][0]=std::abs(cluster_angle[i][j]-TARGET_VALUE);
			target[i][j][1]=i;
		}
	}

	for(int c=0; c<cNUM; c++){
		for(int i=0; i<RANDOM_MAX-1; i++){
			for(int j=i+1; j<RANDOM_MAX; j++){
				if(target[i][c][0]<target[j][c][0]){
					w=target[i][c][0];
					s=target[i][c][1];
					target[i][c][0]=target[j][c][0];
					target[i][c][1]=target[j][c][1];
					target[j][c][0]=w;
					target[j][c][1]=s;
				}
			}
		}
	}	

	for(int i=0; i<cNUM; i++){
		for(int j=0; j<RANDOM_MAX*RANKING_RATE; j++){
			for(int k=0; k<2; k++){
				result[j][i][k]=target[j][i][k];
			}
		}
	}

	for(int i=0; i<cNUM; i++){
		std::cout<<"cluster["<<i+1<<"]:"<<centerpoint[i]<<std::endl;
		for(int j=0; j<RANDOM_MAX; j++){
			if(cluster_angle[j][i]!=0)
				std::cout<<"["<<j+1<<"]:"<<target[j][i][0]<<std::endl;
		}
		std::cout<<std::endl;
	}
	
	for(int c=0; c<cNUM; c++){
		for(int i=0; i<RANDOM_MAX-1; i++){
			for(int j=i+1; j<RANDOM_MAX; j++){
				if(cluster_angle[i][c]<cluster_angle[j][c]){
					w=cluster_angle[i][c];
					cluster_angle[i][c]=cluster_angle[j][c];
					cluster_angle[j][c]=w;
				}
			}
		}
	}
	
	for(int i=0; i<cNUM; i++){
		std::cout<<"cluster["<<i+1<<"]:"<<centerpoint[i]<<std::endl;
		for(int j=0; j<RANDOM_MAX; j++){
			if(cluster_angle[j][i]!=0)
				std::cout<<"["<<j+1<<"]:"<<std::abs(cluster_angle[j][i]-TARGET_VALUE)<<std::endl;
		}
		std::cout<<std::endl;
	}	
*/
}


void Selection(int angle[], int result[][cNUM][2])
{
	int w,s;
	int target[RANDOM_MAX][cNUM][2]={};

	for(int i=0; i<RANDOM_MAX; i++){
		for(int j=0; j<cNUM; j++){
			target[i][j][0]=std::abs(angle[i]-TARGET_VALUE);
			target[i][j][1]=i;
		}
	}
	
	for(int c=0; c<cNUM; c++){
		for(int i=0; i<RANDOM_MAX-1; i++){
			for(int j=i+1; j<RANDOM_MAX; j++){
				if(target[i][c][0]<target[j][c][0]){
					w=target[i][c][0];
					s=target[i][c][1];
					target[i][c][0]=target[j][c][0];
					target[i][c][1]=target[j][c][1];
					target[j][c][0]=w;
					target[j][c][1]=s;
				}
			}
		}
	}	

	for(int i=0; i<cNUM; i++){
		for(int j=0; j<RANDOM_MAX*RANKING_RATE; j++){
			for(int k=0; k<2; k++){
				result[j][i][k]=target[j][i][k];
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

void Crossover(std::bitset<32> parent[][cNUM], std::bitset<32> child[][cNUM])
{
	std::bitset<32> mask = SetMask();
	int counter = 0;
	
	for(int i=0; i<RANDOM_MAX; i+=2)
	{	
		counter += 2;
		for(int k=0; k<cNUM; k++){
			if(counter == INDIVIDUALS_NUMBER)
			{
				mask = SetMaskRandom();
				counter = 0;
			}
			
			for(size_t j=0; j<parent[i][k].size(); j++)
			{
				if(mask.test(j) == 0)
				{
					child[i][k].set(j, parent[i][k].test(j));
					child[i+1][k].set(j, parent[i+1][k].test(j));
				}
				else
				{
					child[i][k].set(j, parent[i+1][k].test(j));
					child[i+1][k].set(j, parent[i][k].test(j));
				}
			}
		}
	}
}

void Mutation(std::bitset<32> child[][cNUM])
{
	double random;
	int mutation_pos;
	
	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int k=0; k<cNUM; k++)
		{
			random = Random(0, 100) * 0.01;
			
			if(random <= MUTATION_RATE)
			{
				mutation_pos = Random(0, MUTATION_POS);
				child[i][k].flip(mutation_pos);
			}
		}
	}
}

int main()
{
	int angle[RANDOM_MAX];
	int centerpoint[cNUM];
	int result[RANDOM_MAX][cNUM][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX][cNUM];
	std::bitset<32> child[RANDOM_MAX][cNUM];

	//std::ofstream ofs(GetTimeISOString() + ".csv");
	
	Initialize(angle);
	
	CenterInitialize(centerpoint);	

	clustering(angle, centerpoint, result);

	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT:" << i << std::endl;
		//ofs << "No." << i+1 << std::endl;
		
		clustering(angle, centerpoint, result);

		Selection(angle, result);

		for(int j=0; j<RANDOM_MAX; j++)
		{
		  for(int i=0; i<cNUM; i++){
			if(parent_cpy == INDIVIDUALS_NUMBER)
			{
				parent_cpy = 0;
			}
			parent[j][i] = BinaryToDecimal(angle[result[parent_cpy][i][1]]);
			parent_cpy += 1;
		  }
		}

		//ofs << "result_angle" << "\t";

		for(int i=0; i<cNUM; i++){
			for(int k=0; k<INDIVIDUALS_NUMBER; k++)
			{
				std::cout << "---- No." << k+1 << " -----" << std::endl;
				std::cout << "result_angle:" << angle[result[k][i][1]] << std::endl;
				//ofs << angle[result[k][1]] << "\t";
			}
		//ofs << std::endl;
		}
	
		std::cout << "----- Crossover -----" << std::endl;
		Crossover(parent, child);

		//ofs << "Crossover" << "\t";
/*
		for(int l=0; l<RANDOM_MAX; l++)
		{
		for(int k=0; k<cNUM; k++){
			//ofs << DecimalToBinary(child[l][k]) << "\t";
			}
		}
		//ofs << std::endl;
*/
		std::cout << "----- Mutation -----" << std::endl;
		Mutation(child);

		//ofs << "Mutation" << "\t";
/*
		for(int l=0; l<RANDOM_MAX; l++)
		{
			for(int i=0; i<cNUM; i++){
			angle[l] = DecimalToBinary(child[l][i]);
			//ofs  << angle[l] << "\t";
		}
		//ofs << std::endl;
		}
*/		
		
	}

	//ofs << "final_result" << "\t";
	Selection(angle, result);
	for(int j=0; j<cNUM; j++){
		std::cout<<"centerpoint["<<j<<"]:"<<centerpoint[j]<<std::endl;
		for(int m=0; m<INDIVIDUALS_NUMBER; m++)
		{
			std::cout << "child[" << m<< "]:" << angle[result[m][j][1]] << std::endl;
			//ofs << angle[result[m][1][i]] << "\t";
		}
		//ofs << std::endl;
		std::cout<<std::endl;
	}
		
	return 0;
}