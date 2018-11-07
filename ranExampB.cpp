#include <iostream>
#include <vector>
#include <set>
#include <array>


using namespace std;

int main()
{
   int N = 5;
   vector<vector<int>> graph(8);

   // Graph Initialization
   graph[0].clear();
   graph[0].push_back(1);
   
   graph[1].clear();
   graph[1].push_back(0);
   graph[1].push_back(7);
   
   graph[2].clear();
   graph[2].push_back(3);
   
   graph[3].clear();
   graph[3].push_back(2);
   
   graph[4].clear();
   graph[4].push_back(5);
   
   graph[5].clear();
   graph[5].push_back(4);
   graph[5].push_back(6);
   
   graph[6].clear();
   graph[6].push_back(5);
   
   graph[7].clear();
   graph[7].push_back(1);
   
   for(int i = 0; i<8;i++)
   {   
       cout<<graph[i].size()<<endl;
       if( !graph[i].empty() )
       { 
           for(int j =0; j<3; j++)
               cout<<graph[i][j]<<" ";
           cout<<endl;
       }
   }   

   set<int> setBA, setBB;
   setBA = { 0, 4, 8, 12 };
   setBB = { 3, 7, 11, 15 };
   bool fba = false;
   bool fbb = false;
   
   array<int,8> selections;
   selections.fill(-1);
   
   for(int i =0;i<8;i++)
       cout<<selections[i]<<" ";
       
   int node = -1;
   int tmpnode = -1;
   cin>>node;
   
   // is there a tree when it applies ?
   // add to the tree
   while( node > -1 )
   {
       // Get the first node - path to which given node connects to
       // Could be connected to more than one.
       
       if( !graph[node].empty() )    // Is connected to at least one node
       {
           tmpnode = graph[node][0]; // Pick the first one 
           cout << tmpnode << endl;
           
           // if given node connects to a node belonging to a path
           // then given node belongs to the same path
           if( selections[tmpnode] != -1 )
               selections[node] = selections[tmpnode];
           else
               selections[node] = node;
               // else given node is the root of the tree 
               // describing the new path
       }

       // check sets 
       // update flags           
       // Check if the added node belong to either of the 
       // sets. It can belong to ONLY one of them
       if( setBA.find(node) != setBA.end() )
            fba = true;
       else if ( setBB.find(node) != setBB.end() )
            fbb = true;
       
       // check if path exists     
       if( fba && fbb )
       {
           cout<< " Winner! "<< endl;
           break;
       }

       // union if required
       // check if path exists 
       
       cin>>node;
   }

   for(int i = 0; i<8;i++)
       cout<<selections[i]<<" ";
        
   return 0;
}