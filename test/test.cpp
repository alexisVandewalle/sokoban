#include "test.h"
#include <iostream>
#include <cstdlib>
#include "Map.h"
#include <assert.h>
#include <sstream>
#include <bits/stdc++.h>
#include "Game.h"
#include "SokoParser.h"
#include "NodeMap.h"
#include <unordered_set> 
#include "Solver.h" 

using namespace std;
using namespace test;
using namespace soko;

int test::testSokoban(){
    cout << "Hello world!" << endl;
    return 0; 
}


int test::testSokoParser(int argc, char* argv[]){
    if(argc != 4){
        cerr << "Invalid number of arguments" << endl;
        cerr << "you should provide <input file path> <output dir> and <map set title>" << endl;
        return EXIT_FAILURE;
    }
    string inFilePath(argv[1]), outDir(argv[2]), mapSetTitle(argv[3]);
    SokoParser myParser(inFilePath, outDir, mapSetTitle);
    myParser.parse();
    return EXIT_SUCCESS; 
}

int test::testMapLoadSave(int argc, char* argv[]){
    if(argc != 3){
        cerr << "Invalid number of arguments" << endl;
        return EXIT_FAILURE;
    }
    string filePath(argv[1]);
    
    cout << "test function to get line and column number of a map" << endl;
    vector<int> lineCol(Map::getNLineColMap(argv[1]));
    assert((lineCol[0]==7) && "test function to get line number");
    assert((lineCol[1]==9) && "test function to get column number");

    cout << "test function to load a sokoban map" << endl;
    Map map(filePath); 
    assert(map.getNLines()==7);
    assert(map.getNCol()==9);
    assert(map.getTitle()=="testMap");
    assert(map.getNTarget()==3);
    assert(map.getNBoxOnTarget()==1);
    vector<int> charPos = map.getCharacterPos();
    assert(charPos.size()==2);
    assert(charPos[0]==4 && charPos[1]==2);

    cout << "test function to display map" << endl;
    map.show();

    cout << "test function to save a map" << endl;
    string saveFilePath(argv[2]);
    map.save(saveFilePath);
    return EXIT_SUCCESS; 
}

int test::testMapMove(int argc, char* argv[]){

    
    MoveType move = static_cast<MoveType>(*argv[1]);
    
    
    string map1_1,map_1_2,map2_1,map2_2,map2_3,map2_4,map2_5,map3,map4_1,map4_2,map4_3,map4_4,map4_5,map5;
    // tests map for a character not on a target
    vector<string> mapsStr = {"# @#", "# @##","# @$#","#@$$ #","#@$* #","#@$. #", "#@$  #", "#@. #", "# @*#","#@*$ #", "#@** #", "#@*. #", "#@*   #", "#@ #"};
    vector<string> expMaps = {"# @#", "# @##","# @$#","#@$$ #","#@$* #","# @* #", "# @$ #", "# + #", "# @*#","#@*$ #", "#@** #", "# +* #", "# +$  #", "# @#"};
    // tests map for a character on a target
    vector<string> mapsStr2 = {"# +#", "# +##","# +$#","#+$$ #","#+$* #","#+$. #", "#+$  #", "#+. #", "# +*#","#+*$ #", "#+** #", "#+*. #", "#+*   #", "#+ #"};
    vector<string> expMaps2 = {"# +#", "# +##","# +$#","#+$$ #","#+$* #","#.@* #", "#.@$ #", "#.+ #", "# +*#","#+*$ #", "#+** #", "#.+* #", "#.+$  #", "#.@#"};

    // all tests and expected maps
    mapsStr.insert(mapsStr.end(), mapsStr2.begin(), mapsStr2.end());
    expMaps.insert(expMaps.end(), expMaps2.begin(), expMaps2.end());
    
    cout << "test move for each map:" << endl;
    for(int i=0; i<mapsStr.size(); i++){
        cout << "input/output/expected - map:" << i << endl;
        
        // init map - flip map for LEFT and UP direction
        if(move==LEFT || move==UP){
            reverse(mapsStr[i].begin(), mapsStr[i].end());
            reverse(expMaps[i].begin(), expMaps[i].end());
        }
        stringstream mapStrI(mapsStr[i]);
        Map map(mapStrI);
        cout << map.toString()<<endl;
        vector<int> initPosV = map.getCharacterPos();
        int initPos = initPosV[1];
        
        // transpose map if necessary
        if(move==UP || move==DOWN){
            map.transpose();
        }

        // call function to move character
        int moveStatus = map.move(move);
        
        // verifications
        
        // check Position update
        vector<int> endPosV = map.getCharacterPos();
        int endPos;
        if(move==UP || move==DOWN){
            assert(endPosV[1]==0);
            endPos = endPosV[0];
        }else{
            assert(endPosV[0]==0);
            endPos = endPosV[1];
        }
        if(moveStatus==MOVE_OK){
            if(move==UP || move==LEFT)
                assert(endPos==(initPos-1));
            else
                assert(endPos==(initPos+1));

        }else{
            assert(endPos==initPos);
        }

        if(move==UP || move==DOWN){
            map.transpose();
        }
        cout << map.toString() << endl << expMaps[i] << endl << endl;
        // check map is expected one
        assert(map.toString()==expMaps[i]);

        // check move status is expected one
        if(expMaps[i]==mapsStr[i]){
            assert(moveStatus==MOVE_KO);
        }else{
            assert(moveStatus==MOVE_OK);
        }

        // check number of box on target is as expected
        int nTargetBoxExp = count(expMaps[i].begin(), expMaps[i].end(), static_cast<char>(BOX_ON_TARGET));
        assert(nTargetBoxExp==map.getNBoxOnTarget());
    }    

    return EXIT_SUCCESS;
}

int test::testInteractiveGame(int argc, char* argv[]){
    string mapPath(argv[1]);
    cout << "Initialize game" << endl;
    Game game(mapPath);
    cout << "Entering game loop:" << endl;
    game.gameLoop();
    cout << "Score:" << endl;
    cout << game.getScore() << endl;
    return EXIT_SUCCESS;
}

int test::testCopyHashMap(int argc, char* argv[]){
    stringstream ss;
    ss << "#####" << "\n";
    ss << "#   #" << "\n";
    ss << "# @.#" << "\n";
    ss << "#####" << "\n";
    ss << "\n";
    ss << "title:test";

    Map m1(ss);
    // try making a copy of m1
    Map m2(m1);
    // test equality operator
    cout << "m1==m2?" << (m1==m2) << endl;
    // test hash computation
    cout << "hash m1: " << m1.getHash() << endl;
    cout << "hash m2: " << m2.getHash() << endl;
    // test if modification on m2 modifies m1
    m2.move(LEFT);
    vector<int> p1(m1.getCharacterPos());
    vector<int> p2(m2.getCharacterPos());
    cout << m1.toString() << endl;
    cout << m2.toString() << endl;
    cout << "p1:" << p1[0] << " " << p1[1] << endl;
    cout << "p2:" << p2[0] << " " << p2[1] << endl;
    cout << "m1==m2?" << (m1==m2) << endl;
    // check two hashes are different
    cout << "hash m1: " << m1.getHash() << endl;
    cout << "hash m2: " << m2.getHash() << endl;

    return EXIT_SUCCESS;
}

int test::testNodeMap(int argc, char* argv[]){
    
    stringstream ss;
    ss << "#####" << "\n";
    ss << "#   #" << "\n";
    ss << "# @.#" << "\n";
    ss << "#####" << "\n";
    ss << "\n";
    ss << "title:test";

    Map m1(ss);
    shared_ptr<NodeMap> n1 = make_shared<NodeMap>(m1);
    shared_ptr<NodeMap> n2 = make_shared<NodeMap>(n1, LEFT);
    shared_ptr<NodeMap> n3 = make_shared<NodeMap>(n2, LEFT);
    // test getMoveSeq is working
    assert(n3->getMoveSeq()=="HH");
    cout << n3->getMoveSeq() << endl;
    cout << "n3==n2?" << (*n3==*n2) << endl;
    cout << "n3==n1?" << (*n3==*n1) << endl;

    cout << "test unordered set" << endl; 
    unordered_set<shared_ptr<NodeMap>, NodeMapHasher, NodeMapKeyEqual> set;

    cout << "insert n1" << endl;
    set.insert(n1);
    assert(set.count(n3)==0);
    cout << "insert n2" << endl;
    set.insert(n2);
    assert(set.count(n3)==1);
    return EXIT_SUCCESS;
}


int test::testSokobanSolver(int argc, char* argv[]){

    Map map(argv[1]);
    cout << "Map to solve:" << endl;
    cout << map.toString() << endl;
    Solver s(map);
    s.run();
    
    if(s.isSolve()){
        // check solution is correct
        cout << "Solution found:" << s.getSolution() << endl;
        cout << "Step by step solution" << endl;
        string solution(s.getSolution());
        for(int i=0; i< solution.length(); i++){
            cout << endl << "Step " << (i+1) << ":" << endl;
            int moveSt = map.move(static_cast<MoveType>(solution[i]));
            assert(moveSt==MOVE_OK);
            cout << map.toString() << endl;
        }
        assert(map.isWin() == true);
    }else{
        cout << "no solution found" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; 
}

int test::testMapLocked(int argc, char* argv[]){
    stringstream ss;
    ss << "#####" << "\n";
    ss << "#   #" << "\n";
    ss << "#@.$#" << "\n";
    ss << "#####" << "\n";
    ss << "\n";
    ss << "title:test";

    Map m1(ss);
    assert(m1.mapLocked());


    stringstream ss2;
    ss << "#####" << "\n";
    ss << "# . #" << "\n";
    ss << "#@$ #" << "\n";
    ss << "#####" << "\n";
    ss << "\n";
    ss << "title:test";

    Map m2(ss2);
    assert(!m2.mapLocked());
    return EXIT_SUCCESS;
}

void test::printHelp(string& progName){
    cout << "This is the program to launch test for the sokoban application" << endl;
    cout << "Usage: " << progName << " testName" << endl;
    cout << endl << "Available tests:" << endl;
    cout << " * testMapLoadSave" << endl;
    cout << " * testMapMove" << endl;
    cout << " * testInteractiveGame" << endl;
    cout << " * testSokoParser" << endl;
    cout << " * testCopyHashMap" << endl;
    cout << " * testNodeMap" << endl;
    cout << " * testSokobanSolver" << endl;
    cout << " * testMapLocked" << endl;
}

int main(int argc, char* argv[]){
    string progName(argv[0]); 
    if(argc < 2){
        printHelp(progName);
        return EXIT_FAILURE;
    }
    string arg(argv[1]);
    if(arg=="--help"){
        printHelp(progName);
        return EXIT_SUCCESS;
    }else if(arg=="testMapLoadSave"){
        cout << "Executing " << arg << endl;
        return testMapLoadSave(argc-1, argv+1);
    }else if(arg=="testMapMove"){
        cout << "Executing " << arg << endl;
        return testMapMove(argc-1, argv+1); 
    }else if(arg=="testInteractiveGame"){
        cout << "Executing " << arg << endl;
        return testInteractiveGame(argc-1, argv+1); 
    }else if(arg=="testSokoParser"){
        cout << "Executing " << arg << endl;
        return testSokoParser(argc-1, argv+1); 
    }else if(arg=="testCopyHashMap"){
        cout << "Executing " << arg << endl;
        return testCopyHashMap(argc-1, argv+1); 
    }else if(arg=="testNodeMap"){
        cout << "Executing " << arg << endl;
        return testNodeMap(argc-1, argv+1); 
    }else if(arg=="testSokobanSolver"){
        cout << "Executing " << arg << endl;
        return testSokobanSolver(argc-1, argv+1); 
    }else if(arg=="testMapLocked"){
        cout << "Executing " << arg << endl;
        return testMapLocked(argc-1, argv+1); 
    }else{
        cerr << "Unknown test name" << endl;
        return EXIT_FAILURE;
    } 
        
    return 0;
}
