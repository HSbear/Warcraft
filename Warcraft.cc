#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int WARRIOR_NUM = 5;
const int ARMS_NUM =3;

string warrior[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string arms[ARMS_NUM] = {"sword", "bomb", "arrow"};
int createWarrior[WARRIOR_NUM];
int produceSeq[2][WARRIOR_NUM] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};

class headQuarters;//前向声明
class Warrior
{
public:
    Warrior(headQuarters* p,int id,int warriorType);
    void print(int time);
    void printAlready(string s);
private:
    int _warriorType;
    int _id;
    int _loyalty;
    double _morale;
    headQuarters * _pheadquarters;
    int _armsType[2];
};

class headQuarters
{
public:
    headQuarters(int color,int totalLifeValue);
    ~headQuarters();
    int produce(int time);
    string getColor();
    friend class Warrior;
private:
    int _color;
    int _totalLifeValue;
    int _totalWarriorNum;
    bool _stoped;
    int _curIdx;
    int _warrior[WARRIOR_NUM];
    vector<Warrior*> _pWarriors;
};

Warrior::Warrior(headQuarters* p,int id,int warriorType)
: _warriorType(warriorType)
, _id(id)
, _loyalty(0)
, _morale(0)
, _pheadquarters(p)
{
    if(warrior[_warriorType] == "dragon"){
        _morale=(double)p->_totalLifeValue/createWarrior[_warriorType];
        _armsType[0]=_id % ARMS_NUM;
    }else if(warrior[_warriorType] == "ninja"){
        _armsType[0]=_id % ARMS_NUM;
        _armsType[1]=(_id+1) % ARMS_NUM;
    }else if(warrior[_warriorType] == "iceman"){
        _armsType[0]=_id % ARMS_NUM;
    }else if(warrior[_warriorType] == "lion"){
        _loyalty=p->_totalLifeValue;
    }
}

void Warrior::printAlready(string s)
{
    if(s == "dragon"){
        cout << "It has a "<< arms[_armsType[0]] <<
        ",and it's morale is " << _morale << endl;
    }else if(s == "ninja"){
        cout << "It has a " << arms[_armsType[0]] <<
        " and a " << arms[_armsType[1]] << endl;
    }else if(s == "iceman"){
        cout << "It has a " << arms[_armsType[0]] <<
        endl;
    }else if(s == "lion"){
        cout << "It's loyalty is " << _loyalty << endl;
    }
}

void Warrior::print(int time)
{
    string color=_pheadquarters->getColor();
    printf("%03d",time);
    cout <<" "<<color<<" "<<warrior[_warriorType]<<" "<< _id
         <<" born with strength "<<createWarrior[_warriorType]<<","
         <<_pheadquarters->_warrior[_warriorType]<<" "<<warrior[_warriorType]
         <<" in "<<color<<" headQuarters"<< endl;
    printAlready(warrior[_warriorType]);
}

headQuarters::headQuarters(int color,int totalLifeValue)
: _color(color)
, _totalLifeValue(totalLifeValue)
, _totalWarriorNum(0)
, _stoped(false)
, _curIdx(0)
{
    for(int i=0;i<WARRIOR_NUM;i++)
    {
        _warrior[i] = 0;
    }
}

headQuarters::~headQuarters()
{
    for(auto &i:_pWarriors)
    {
        delete i;
    }
}

int headQuarters::produce(int time)
{
    if(_stoped)
        return 0;
    
    for(int i=0;i<WARRIOR_NUM;i++)
    {
        if(createWarrior[produceSeq[_color][_curIdx]] > _totalLifeValue)
        {
            _curIdx = (_curIdx+1) % WARRIOR_NUM;
            continue;
        }else {
            break;
        }
    }
    int warriorType = produceSeq[_color][_curIdx];
    if(createWarrior[produceSeq[_color][_curIdx]] > _totalLifeValue)
    {
        _stoped = true;
        if(_color == 0)
        {
            printf("%03d",time);
            cout << " red headquarter stops making warriors" << endl;
        }else {
            printf("%03d",time);
            cout << " blue headquarter stops making warriors" << endl;
        }
        return 0;
    }
    _totalLifeValue -= createWarrior[warriorType];
    _curIdx = (_curIdx+1) % WARRIOR_NUM;
    _pWarriors.push_back(new Warrior(this ,_totalWarriorNum+1, warriorType));
    _warrior[warriorType]++;
    _pWarriors[_totalWarriorNum]->print(time);
    _totalWarriorNum++;
    return 1;
}

string headQuarters::getColor()
{
    if(_color == 0){
        return "red";
    }else {
        return "blue";
    }
}

int main()
{
    int exp,lifeValue;
    cin >> exp;//样例个数
    cin >> lifeValue;
    int no=1;
    while(exp--){
        for(int i=0;i<WARRIOR_NUM;i++)
        {
            scanf("%d",&createWarrior[i]);
        }
        cout << "case:"<< no++ << endl;
        headQuarters red(0,lifeValue);
        headQuarters blue(1,lifeValue);

        int time=0;
        while(1){
            int status1=red.produce(time);
            int status2=blue.produce(time);
            if(!status1 && !status2)
            {
               break;
            }else {
                time++;
            }
        }
    }
    return 0;
}