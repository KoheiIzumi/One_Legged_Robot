#include "FileManager.h"


FileManager::FileManager(void)
{
}


FileManager::~FileManager(void)
{
}

bool FileManager::OpenInputFile(char* name)
{
	ifs.open(name, std::ios::in);
	if(!ifs)
	{
		cout << "�t�@�C�������݂��Ȃ����߁A�I�����܂����B" << endl;
		ifs.close();
		return false;
	}
	else if(ifs.fail())
	{
		cout << "�ǂݎ��Ɏ��s���܂����B" << endl;
		return false;
	}
	return true;
}

int FileManager::GetData(void)
{
	std::string _ret;
	if(!ifs.eof()){
		getline(ifs,_ret,',');
		int ret = stoi(_ret);
		return ret;
	}
	return 0;
}

void FileManager::CloseInputFile(void)
{
	ifs.close();
}

void FileManager::OpenOutputFile(char* name)
{
	ofs.open(name, std::ios::out);
}

void FileManager::PutData(int val)
{
	ofs << val << ',';
}

void FileManager::PutData(std::string  str)
{
	ofs << str;
}

void FileManager::CloseOutputFile(void)
{
	ofs.close();
}

void FileManager::PutEndline()
{
	ofs << endl;
}

void FileManager::DisplayAllData()
{
	while(!ifs.eof())
	{
		std::string str;
		getline(ifs,str,',');
		cout << str << ' ';
	}
}

int FileManager::stoi(std::string str)
{
	int ret;
	std::stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}