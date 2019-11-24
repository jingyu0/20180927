#include <map>
#include <set>
#include <string>

void test_map_set1()
{
	set<int> s;
	s.insert(3);
	s.insert(5);
	s.insert(8);
	s.insert(1);
	s.insert(9);

	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	set<int>::reverse_iterator rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	//s.erase(5);

	auto pos = s.find(5); // O(logN)
	// auto pos = std::find(s.begin(), s.end(), 5); // O(N)
	if (pos != s.end())
	{
		s.erase(pos);
	}
	else
	{
		cout << "�Ҳ���" << endl;
	}

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_map_set2()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("insert", "����"));
	dict.insert(pair<string, string>("left", "���"));
	dict.insert(pair<string, string>("right", "�ұ�"));
	dict.insert(pair<string, string>("node", "�ڵ�"));
	dict.insert(pair<string, string>("tree", "��"));
	dict["sort"] = "����";

	/*string str;
	while (cin >> str)
	{
	auto ret = dict.find(str);
	if (ret != dict.end())
	{
	cout << str << ":" << (*ret).second << endl;
	}
	else
	{
	cout << str << ":" << "�Ƿ��ʻ�" << endl;
	}
	}*/

	//string strs[] = { "ƻ��", "����", "��ݮ", "��ݮ", "����", "��ݮ" };
	//map<string, int> countMap;
	//for (auto& e : strs)
	//{
	////	map<string, int>::iterator ret = countMap.find(e);
	//	auto ret = countMap.find(e);
	//	if (ret != countMap.end())
	//	{
	//		//(*ret).second++;
	//		ret->second++;
	//	}
	//	else
	//	{
	//		// ���ù��캯��������������
	//		//countMap.insert(pair<map<string, int>(e, 1));

	//		// template<class K, class V>
	//		/*inline pair<K, V> make_pair(const K& k, const V& v)
	//		{
	//			return pair<K, V>(k, v);
	//		}*/
	//		countMap.insert(make_pair(e, 1));
	//	}
	//}

	//string strs[] = { "ƻ��", "����", "��ݮ", "��ݮ", "����", "��ݮ" };
	//map<string, int> countMap;
	//for (auto& e : strs)
	//{
	//	//	map<string, int>::iterator ret = countMap.find(e);
	//	auto ret = countMap.find(e);
	//	if (ret != countMap.end())
	//	{
	//		//(*ret).second++;
	//		ret->second++;
	//	}
	//	else
	//	{
	//		// ���ù��캯��������������
	//		//countMap.insert(pair<map<string, int>(e, 1));

	//		// template<class K, class V>
	//		/*inline pair<K, V> make_pair(const K& k, const V& v)
	//		{
	//		return pair<K, V>(k, v);
	//		}*/
	//		countMap.insert(make_pair(e, 1));
	//	}
	//}

	/*V& operator[](const K& k)
	{
		pair<iterator, bool> ret = insert(make_pair(k, V()));
		return ret.first->second;
	}*/
	string strs[] = { "ƻ��", "����", "��ݮ", "��ݮ", "����", "��ݮ" };
	map<string, int> countMap;
	for (auto& e : strs)
	{
		countMap[e]++;
	}

	countMap["�㽶"];
	countMap["�㽶"] = 5;


	/*string strs[] = { "ƻ��", "ƻ��","ƻ��","����", "��ݮ", "��ݮ", "����", "��ݮ" };
	map<string, int> countMap;
	for (auto& e : strs)
	{
	pair<map<string, int>::iterator, bool> ret = countMap.insert(make_pair(e, 1));
	if (ret.second == false)
	{
	ret.first->second++;
	}
	}*/
}