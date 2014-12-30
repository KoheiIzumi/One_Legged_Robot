#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define NUM 10
#define cNUM 3

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


int main()
{
	int num[NUM], cnum[cNUM];
	int result[NUM][cNUM];
	srand((unsigned int)time(NULL));

	ofstream ofs(std::to_string((unsigned int)time(NULL)) + ".csv");

	for(int i=0; i<NUM; i++){
		num[i]=GetRandom(0,100);
		cout<<"No["<<i<<"] = "<<num[i]<<endl;
	}

	cout << endl;

	for(int j=0; j<cNUM; j++){
		cnum[j]=GetRandom(0,100);
			cout<<"centerNo["<<j<<"]="<<cnum[j]<< endl;
		}

	cout<<endl;

	bool loop=true;

	while(loop){
	
	for(int i=0; i<NUM; i++){
		for(int j=0; j<cNUM; j++){
			result[i][j]=abs(num[i]-cnum[j]);
			cout<<"result["<<i<<"]["<<j<<"]="<<result[i][j]<<endl;
				
		}
	}
	cout<<endl;

	int min[NUM][2];
	for(int i=0; i<NUM; i++){
		min[i][0] = result[i][0];
		min[i][1] = 0;
		for(int j=0; j<cNUM; j++){
			if(result[i][j]<min[i][0]){
				min[i][0]=result[i][j];
				min[i][1]=j;
			}
		}
		//cout<<"min ["<<i<<"][0]: "<<min[i][0]<<endl;
		//cout<<"min[" <<i<<"][1]: "<<min[i][1]<<endl;
	}

	int point_counter[cNUM]={};
	int sum[cNUM]={};
	int newcenter[cNUM]={};
	int count_Group[cNUM]={};
	for(int i=0;i<NUM;i++)
	{
		for(int j=0;j<cNUM;j++)
		{
			if(min[i][1]==j)
			{
				point_counter[j]++;
				sum[j] += num[j];
				newcenter[j]=sum[j]/cnum[j];
				count_Group[j]++;
			}
		}
	}

	 int same_count = 0;
	 for(int j=0;j<cNUM; j++){
           
 
            if(count_Group[j] != 0){
				if((sum[j] / count_Group[j]) == cnum[j])
                        same_count ++;
               
                cnum[j] = sum[j] / count_Group[j];
                
            }
			if(same_count == cNUM){
                loop=false;
            }
			cout<<"new centerpoint:"<<cnum[j]<<endl;
	 }cout<<endl;
	}

	/*

	for(int i=0; i<NUM; i++)
	{
		cout<<"----- "<<i<<"�Ԗڂ̌� -----"<<endl;
		cout<<"�̂̐��l: "<<num[i]<<endl;
		cout<<"�Z���^�[�|�C���g�̈ʒu"<<cnum[min[i][1]]<<endl;
		cout<<"�Z���^�[�|�C���g�̋���: "<<min[i][0]<<endl;
		cout<<"��������Z���^�[�|�C���g: "<<min[i][1]<<endl;
		ofs<<num[i]<<"\t"<<cnum[min[i][1]]<<"\t"<<min[i][0] <<"\t"<<min[i][1]<<endl;
	}
	for(int i=0;i<cNUM;i++)
	{
		cout<<i<<"�Ԗڂ̃Z���^�[�|�C���g�ɏ��������: "<<point_counter[i]<<endl;
		cout<<"�̂̒l�̍��v"<<sum[i]<<endl;
	}

	cout<<endl;

	for(int j=0; j<cNUM; j++){
		cout<<"�V�������S�_: "<<new_centerpoint[j]<<endl;
	}
	*/
}