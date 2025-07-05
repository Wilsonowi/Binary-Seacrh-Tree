#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item

		//find deepest node
		bool deepestNodes();
		void deepestNodes2(BTNode*,int, int&);
		void printDeepestNodes(BTNode*, int, int);

		//display student info
		bool display(int, int);
		void displayAsc(ostream&, BTNode*);
		void displayDesc(ostream&, BTNode*);

		//Clone Tree

		bool CloneSubtree(BST , type );
		bool CloneSubTree2(BST , BST* , BTNode* , type );
		bool CloneSubTree3(BST* , BTNode* );

		bool searchItem(BTNode* , type , BTNode*& );
		void EmptyClone();
		void RemoveSubTreeNodes(BTNode*);

		// Part 5             
		bool printLevelNodes();

		// Part 6
		bool printPaths();                      
		int printPathsRecur(BTNode* cur, int path[], int pathLen);
		void printArray(int ints[], int len);
};

#endif