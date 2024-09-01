#include <iostream>
#include <vector>

using namespace std;

int N; // 채팅방 수
struct Node {
    bool alarm = true;
    int parent = 0;
    int power = 0;
    vector<int> child;
};
Node nodes[100001];
int sum = 0;

void input() {
    vector<int> inputs;
    int t;
    
    inputs.push_back(-1);
    for(int i = 1;i <= N * 2;i++) {
        cin>>t;
        inputs.push_back(t);
    }
    
    for(int i = 1;i <= N;i++) {
        Node temp;
        temp.parent = inputs[i];
        temp.power = inputs[i + N];
        nodes[i] = temp;
    }
    
    for(int i = 1;i <= N;i++) {
        int parentNum =  nodes[i].parent;
        nodes[parentNum].child.push_back(i);
    }
}

void swapParents(const int c1, const int c2) {
    Node copyC1 = nodes[c1];
    Node copyC2 = nodes[c2];
    
    // [C1 <- C2]
    // 2. 부모 노드로 가서 자식 노드 변경
    int parentNum = nodes[c1].parent;
    for(int i = 0;i < nodes[parentNum].child.size();i++) {
        int childNum = nodes[parentNum].child[i];
        
        if (childNum == c1) {
            nodes[parentNum].child[i] = c2;
            break;
        }
    }
    // 3. 부모 노드 변경
    nodes[c2].parent = nodes[c1].parent;
    
    // [C2 <- C1]
    // 2. 부모 노드로 가서 자식 노드 변경
    parentNum = copyC2.parent;
    for(int i = 0;i < nodes[parentNum].child.size();i++) {
        int childNum = nodes[parentNum].child[i];
        
        if (childNum == c2) {
            nodes[parentNum].child[i] = c1;
            break;
        }
    }
    // 3. 부모 노드 변경
    nodes[c1].parent = copyC2.parent;
}

void dfs(int c, int depth) {
    // 알람 꺼져 있으면 종료
    if (nodes[c].alarm == false)
        return;
    
    // 초기 권한 세기가 안맞으면 종료 ==> 이러면 안됨 그 밑에 어떤게 있을 줄 모름
    if (nodes[c].power >= depth)
        sum += 1;
    
//    sum += 1;
//    cout<<"depth: "<<depth<<", c: "<<c<<"\n";
    
    for(int i = 0;i < nodes[c].child.size();i++) {
        int childNum = nodes[c].child[i];
        dfs(childNum, depth + 1);
    }
}

int searchAlarm(int c) {
    sum = 0;

    for(int i = 0;i < nodes[c].child.size();i++) {
        int childNum = nodes[c].child[i];
        
        dfs(childNum, 1);
    }
//    cout<<endl;
    
    return sum;
}

int main() {
    int Q;
    cin>>N>>Q;
    
    int command;
    while(Q--) {
        cin>>command;
        
        // 1. 사내 메신저 준비
        if (command == 100) {
            input();
        }
        // 2. 알림망 설정 on/off
        else if (command == 200) {
            int c;
            cin>>c;
            
            nodes[c].alarm = !nodes[c].alarm;
        }
        // 3. 권한 세기 변경
        else if (command == 300) {
            int c, newPower;
            cin>>c>>newPower;
            
            nodes[c].power = newPower;
        }
        // 4. 부모 채팅방 교환
        else if (command == 400) {
            int c1, c2;
            cin>>c1>>c2;
            
            swapParents(c1, c2);
        }
        // 5. 알림을 받을 수 있는 채팅방 조회
        else {
            int c;
            cin>>c;
            
            int result = searchAlarm(c);
            cout<<result<<endl;
        }
    }
    return 0;
}