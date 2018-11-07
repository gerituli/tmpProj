#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <map>


using namespace std;

class mPath{
    
    public:
        int root;
        bool fA;
        bool fB;
        int rank;
    
        mPath( int mroot ):rank(0)
        { 
            this->root = mroot;
            this->fA = false;
            this->fB = false;
            cout<<"A path creation with "<<( this->root )<<endl;
        }
        // A Union method should be developed
};


class Board{

    int bsize;
	int totnodes;
    vector<vector<int>> graph(9);

	Board( int bsize ):bsize(bsize)
	{
	 
	this->totnodes = ( bsize*bsize );
	
	graph.resize( totnodes );
	
	   // Graph Initialization
   for( int i = 0; i<totnodes; i++ )
   {
       graph[i].clear();
   }
   
   for( int i = 0; i<totnodes; i++ )
   {
        if( (i+1)%bsize != 0 )   
       {
           graph[i].push_back(i+1);
           graph[i+1].push_back(i);
       }
       if( i+bsize < totnodes )
       {
           graph[i].push_back(i+bsize);
           graph[i+bsize].push_back(i);
       }
   }
   
   for( int i = bsize; i<totnodes; i++ )
   {
       if( i/bsize != (i-2)/bsize )
       {
           graph[i].push_back(i-2);
           graph[i-2].push_back(i);
       }
   }
   
   
   for(int i = 0; i<totnodes;i++)
   {   
       int tmpsize = graph[i].size();
       cout<<i<<" : "<<graph[i].size()<<endl;
       if( !graph[i].empty() )
       { 
           for(int j =0; j<tmpsize; j++)
               cout<<graph[i][j]<<" ";
           cout<<endl;
       }
   }   
   // --------- End of Graph Initialization ---------
	
	
  }
	
	

};






int main()
{





   set<int> setBA, setBB;
   setBA = { 0, 3, 6 };
   setBB = { 2, 5, 8 };

   
   array<int,9> selections;
   selections.fill(-1);
   
   // Not an array: Cannot use of reference for reference
   // Not a vector: references are not assignable OR copyable to be checked
   
   map<int,mPath*> indexes;
   
   for(int i =0;i<9;i++)
       cout<<selections[i]<<" ";
       

   bool isWinner = false;
   int node = -1;
   int count = 0;
   
   
   // A Vector containing all legal moves at any time 
   set<int> listmoves = {4,7,5,3,1,6,2,0,8};
   bool turn = 0;
   
   

   while( isWinner == false )
   {
        
       cin>>node;
       auto isatpos = listmoves.find(node); 
       if( isatpos != listmoves.end() )
           listmoves.erase( isatpos );
       //--count++;
       // Get a node 
       
       turn = turn ? false:true;
       
       cout<<endl<<"Selection :"<<node<<" "<<( turn ? "blue" : "red")<<endl;
       // A one node Path created and initialized
       mPath* curNodePath = new mPath(node);
       // Path map updated
       indexes[node] = curNodePath;
       
       // temporary variable
       mPath* aPath = indexes[node];
       
       // array node - root mapping
       selections[node] = node;
       
       // check sets 
       // update flags           
       // Check if the added node belong to either of the 
       // sets. It can belong to ONLY one of them
       if( setBA.find(node) != setBA.end() )
            curNodePath->fA = true;
       else if ( setBB.find(node) != setBB.end() )
            curNodePath->fB = true;

     cout<<"A_Results "<<curNodePath->fA<<" "<<curNodePath->fB<<endl;

        for( auto& mp : indexes )
            cout<<mp.first<<" "<<(mp.second)->root<<endl;
        
       if( !graph[node].empty() )    // Is connected to at least one node
       {
          
           for( auto tmpnode : graph[node]  ){
               // For every node connected to the selected check if 
               // a set already exists if yes then selected node 
               // belongs to that set
               // if more than two adjacent nodes belong to different
               // sets then the two sets should be combined!
              
              // if given node connects to a node belonging to a path
              // then given node belongs to the same path
              if( selections[tmpnode] != -1 )
              {
                  // Unite Paths
                  aPath = indexes[tmpnode];
                  // Unite to curNodePath
                  
                      //aPath->root = aPath->root;
                      aPath->fA |= curNodePath->fA;
                      aPath->fB |= curNodePath->fB;
                      aPath->rank += curNodePath->rank;
                      
                  
                  
                  // update selections 
                  for( int id =0; id<8;id++)
                  {
                      // cout<<"Searching for "<<curNodePath->root<<endl;
                      if(selections[id] == curNodePath->root)
                      {
                          cout<<"Found"<<id<<endl;
                          selections[id] = aPath->root;
                          cout<<" "<<selections[id]<<" "<<(aPath->root)<<endl;
                      }
                  }
                  
                  // delete old pointer 
                  //delete indexes[node];
                  
                  // replace old pointer with new one
                  indexes[node] = aPath;
                  curNodePath = indexes[node];
                  cout<<"Unification happenned"<<endl;
              }
              else
                 cout<<"No unification"<<endl;

           }

       }

       // check if path exists     
       // nodes belong to the same mPath class : same set index
       // and this mPath has at least one from each terminal set
       cout<<"Results "<<curNodePath->fA<<" "<<curNodePath->fB<<endl;
       if( curNodePath->fA && curNodePath->fB )  
       {
           cout<< " Winner! "<< endl;
           isWinner = true;
       }
       if( count == 5 )
           break;

   }

   cout<<"Final configuration"<<endl;
   for(int i = 0; i<9;i++)
       cout<<selections[i]<<" ";
           
        
   return 0;
}