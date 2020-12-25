#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> undist(vector<vector<string>> vect, vector<vector<string>> state_table)
{
	vector<vector<string>> res;
	vector<vector<string>> new_table_state; // ������� ��������� ��� ������������
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i].size() == 1)
			res.push_back(vect[i]);
		else
		{
			for (int j = 0; j < vect[i].size(); j++)
			{
				// ������ � ������� ��������� ������ ������� � �������� �� ������
				int ind = 0;
				for (int kk = 0; kk < state_table.size(); kk++)
				{
					if (state_table[kk][0] == vect[i][j])
					{
						ind = kk;
						//break;
					}
				}
				new_table_state.push_back(state_table[ind]);
			}
		}
	}

	// ��������� �� ��������������
	for (int i = 0; i < new_table_state.size(); i++)
	{
		for (int j = i + 1; j < new_table_state.size(); j++) // ���������� ������� �������
		{
			for (int k = 1; k < new_table_state[i].size(); k++)
			{
				if (new_table_state[i][k] != new_table_state[j][k]) // ���� ����� ��������������, ���������� ���������
				{
					res.push_back(vector<string> {new_table_state[i][0]});
					res.push_back(vector<string> {new_table_state[j][0]});
					break;
				}
				if (k == (new_table_state[i].size() - 1))
				{
					res.push_back(vector<string> {new_table_state[i][0]});
				}
			}
		}
	}

	return res;
}

// ���������� �� �����
vector<vector<string>> algorithm(string fname)
{
	vector<vector<string>> states;
	vector<char> alf;
	string line; // ������, ������� �������
	ifstream in(fname); // �������� ���� ��� ������
	int start_nuber = 0; // ������ ����� - ����� ���������� ���������
	vector<int> finish_states; // ����� - ������ ��������� ���������
	if (in.is_open())
	{
		getline(in, line);
		// ����������� ������ ������
		start_nuber = line[0] - '0'; 
		for (int i = 2; i < line.length(); i++)
		{
			if (line[i] != ',') {
				finish_states.push_back(line[i] - '0');
			}
		}

		// ������������ ������ ������
		getline(in, line);
		alf.push_back(line[0]); // ����� ������� ������� == #
		for (int i = 2; i < line.length(); i++)
		{
			if (line[i] != ' ')
				alf.push_back(line[i]);
		}

		// ������������ ��� ��������� ������
		int k = 0;
		while (getline(in, line))
		{
			vector<string> v;
			string s = "";
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != ' ')
				{
					s += line[i];
				}
				else
				{
					if (s.length() != 0)
					{
						v.push_back(s);
						s = "";
					}
				}
			}
			states.push_back(v);
			k++;
		}
	}
	in.close();

	vector<vector<string>> set;
	// ������� ��������� ���������� � ��������� ���������
	vector<string> vect;
	vect.push_back(states[start_nuber][0]);
	set.push_back(vect); // ���������
	vect.clear();
	for (int i = 0; i < finish_states.size(); i++)
	{
		vect.push_back(states[finish_states[i]][0]);
	}
	set.push_back(vect);
	vector<vector<string>> undist_sets = undist(set, states);

	vector<vector<string>> result;
	vector<string> tmp;
	for (auto x : alf)
	{
		tmp.push_back(string(1, x));
	}
	result.push_back(tmp); // �������� ������ ������� � ���������

	// ������ ������� ������ � ����������� �����������
	for (int i = 0; i < states.size(); i++)
	{
		for (int j = 0; j < undist_sets.size(); j++)
		{
			if (states[i][0] == undist_sets[j][0])
				result.push_back(states[i]);
		}
	}


	return result;
}

int main()
{
	setlocale(LC_ALL, "ru");

	vector<vector<string>> v = algorithm("test1.txt");

	cout << "���������������� ������� ���������:" << endl;
	for (auto x : v)
	{
		for (auto xx : x)
		{
			cout << xx << " ";
		}
		cout << endl;
	}

	cout << endl;

	cout << "===============" << endl;
	v = algorithm("test2.txt");
	cout << "���������������� ������� ���������:" << endl;
	for (auto x : v)
	{
		for (auto xx : x)
		{
			cout << xx << " ";
		}
		cout << endl;
	}
}