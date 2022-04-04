#include "subset_cons.h"
#include <fstream>

#define MARKED 1
#define UNMARK 2
#define DFA_FIRST_STATE 1

int DfaTableGrap[256][256] = {0};

int GetNodeEpsilonState(set<int>& closure, GraphNode** graph, int node)
{
    set<int> nodeEpsilonState;
    nodeEpsilonState.insert(node);
    closure.insert(node);
    while (!nodeEpsilonState.empty()) {
        node = *nodeEpsilonState.begin();
        nodeEpsilonState.erase(node);
        GraphEdge* edge = graph[node]->firstEdge;
        while (edge != NULL && edge->value == '$') {
            closure.insert(edge->vex);
            nodeEpsilonState.insert(edge->vex);
            edge = edge->next;
        }
    }
    return 0;
}

void ClosureMove(set<int>& closure, GraphNode** graph, int inputNode, int edgeChar)
{

    set<int> nodeState;
    nodeState.insert(inputNode);
    map<int, int> nodeIsMove;
    while (!nodeState.empty()) {
        inputNode = *nodeState.begin();
        nodeState.erase(inputNode);

        if (nodeIsMove[inputNode] == 1) {
            continue;
        }
        GraphEdge* edge = graph[inputNode]->firstEdge;
        while (edge != NULL && (edge->value == '$' || edge->value == edgeChar)) {
            closure.insert(edge->vex);
            nodeState.insert(edge->vex);
            edge = edge->next;
        }
        nodeIsMove[inputNode] = 1;
    }
}


int GetUnMarkClosure(map<set<int>, int> &markClosure, set<int>& beginState)
{
    std::map<set<int>, int>::iterator it;
    for (it = markClosure.begin(); it != markClosure.end(); ++it) {
        if (it->second == UNMARK) {
            beginState = it->first;
            return 1;
        }
    }
    return 0;
}


void PrintDfaStateResult(vector<DfaTable> &nfaTableResult,
                        map<set<int>, int> &nfaStateResult,
                        int endState)
{

    std::ofstream  of;
    std::set<int>::iterator it;
    map<char, char> NState;

    of.open("../py_code/input.txt", std::ios::out);

    printf("================================================================\n");
    printf("%10s %10s %10s %20s\n", "BEGIN", "TRANS", "END", "STATE NUMBER");
    printf("================================================================\n");
    for (int row = 0; row < nfaTableResult.size(); ++row) {
        set<int> state1 = nfaTableResult[row].beginState;
        printf("%10d", nfaStateResult[state1]);
        printf("%10c", nfaTableResult[row].trans);
        of << nfaStateResult[state1] << ", ";
        set<int> state2 = nfaTableResult[row].endState;
        printf("%10d %10c", nfaStateResult[state2], ' ');
        
        DfaTableGrap[nfaStateResult[state1]][nfaTableResult[row].trans] = nfaStateResult[state2];

        if (nfaStateResult[state2] == endState) {
            NState[nfaStateResult[state1]] = 'N';
        }

        for (it = state2.begin(); it != state2.end(); ++it) {
            printf("%d,", *it);
        }
        of << nfaStateResult[state2] << ", " << nfaTableResult[row].trans <<std::endl;
        printf("\n");
    }
    of.close();
    printf("================================================================\n");
    
    std::map<set<int>, int>::iterator mit;
    for (mit = nfaStateResult.begin(); mit != nfaStateResult.end(); ++mit) {
        if (NState[mit->second] == 'N') {
            printf("%d -> %c\n", mit->second, 'N');
        } else {
            printf("%d -> %c\n", mit->second, 'A');
        }
    }

}


void RegSearchInputs(int begin, int end, vector<string>& inputs)
{
    printf("begin: %d, end: %d\n", begin, end);
    for (int i = 0; i < inputs.size(); ++i) {
        printf("%s", inputs[i].c_str());
        int j = 0;
        int next = begin;
        while (j < inputs[i].size() && DfaTableGrap[next][inputs[i][j]] != end) {
            next = DfaTableGrap[next][inputs[i][j]];
            j += 1;
        }
        if (DfaTableGrap[next][inputs[i][j]] == end) {
            printf(" -> SUCCESS!\n");
        } else {
            printf("\n");
        }
    }
}

void SubSetConstruction(GraphNode** graph, int begin, int end, vector<string>& inputs)
{
    std::set<int>::iterator it;
    map<set<int>, int> markClosure;
    set<int> closure;
    vector<DfaTable> nfaTableResult;
    map<set<int>, int> nfaStateResult;
    DFARegState regState;
    
    GetNodeEpsilonState(closure, graph, begin);
    markClosure[closure] = UNMARK;
    set<int> beginState;
    int dfaState = DFA_FIRST_STATE;
    regState.beginState = dfaState;
    while (GetUnMarkClosure(markClosure, beginState)) {   
        if (!nfaStateResult[beginState]) {
            nfaStateResult[beginState] = dfaState;
            regState.endState = dfaState;
            dfaState++;
        }
        markClosure[beginState] = MARKED;
        for (int trans = 0; trans <= 255; ++trans) { // ASSIC码表为0-255
            set<int> endState;
            for (it = beginState.begin(); it != beginState.end(); ++it) {
                if (graph[*it]->firstEdge == NULL) {
                    continue;
                }
                int value = graph[*it]->firstEdge->value;
                if (trans == value) {
                    ClosureMove(endState, graph, *it, value);
                }
            }
            if (endState.empty()) {
                continue;
            }
            DfaTable tableRow;
            tableRow.beginState = beginState;
            tableRow.trans = trans;
            tableRow.endState = endState;
            nfaTableResult.push_back(tableRow);
            if (markClosure[endState] != MARKED) {
                markClosure[endState] = UNMARK;
            }
        }
    }
 
    PrintDfaStateResult(nfaTableResult, nfaStateResult, regState.endState);
    RegSearchInputs(regState.beginState, regState.endState, inputs);
}
