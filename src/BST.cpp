#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


//find deepest node in tree
// member 1
bool BST::deepestNodes() {
	int height = 0;

	if (empty()) return false;
	deepestNodes2(root,0 , height); //recursive case: find deepest nodes
	cout << "Deepest nodes: ";
	printDeepestNodes(root, 0, height); //recursive case: call to display the node
	return true;
}


void BST::deepestNodes2(BTNode* cur, int currentLevel, int& height) {
	if (cur == NULL) return;

	if (currentLevel > height) //update the height if current level is bigger
		height = currentLevel;
	deepestNodes2(cur->left, currentLevel + 1 ,height); // move to left node and increase the current level by 1
	deepestNodes2(cur->right, currentLevel + 1, height); // move to right node
	return;
}


void BST::printDeepestNodes(BTNode* cur, int currentLevel, int height) {
	if (cur == NULL) return;
	
	if (currentLevel == height) //if the current level equal to the height means deepest, then display
		cout << cur->item.id << "\t";
	else {
		printDeepestNodes(cur->left, currentLevel + 1, height); //move to left and repeat same process
		printDeepestNodes(cur->right, currentLevel + 1, height); //move to right and repeat same process
	}

}

//display student information
//member 2
bool BST::display(int order, int source) {
	ofstream outfile;
	if (root == NULL)return false; //if empty tree,return false
	if (order == 1) { //ascending
		if (source == 1) {
			displayAsc(cout,root);
		}
		else
		{
			outfile.open("student-info.txt"); //open file to write output
			displayAsc(outfile, root);// call function write into file in ascending order
			outfile.close();
			cout << "Successfully printed in student-info.txt!" << endl;
		}
	}
	else  //descending
	{
		if (source == 1) //display on screen
			displayDesc(cout, root); 
		
		else //display in file
		{
			outfile.open("student-info.txt");
			displayDesc(outfile, root);// call function write into file in descending order
			outfile.close();
			cout << "Successfully printed in student-info.txt!" << endl;
		
		}
	}
	return true;
}
void BST::displayAsc(ostream& source, BTNode* cur) {
	//if root is null, it will return back to node above
	if (cur == NULL) return;
	//use in order to print ascending order
	displayAsc(source,cur->left);
	cur->item.print(source);
	displayAsc(source,cur->right);
	return;
}

void BST::displayDesc(ostream& source, BTNode* cur) {
	//if root is null, it will return back to node above
	if (cur == NULL) return;
	//use in order to print descending order
	displayDesc(source, cur->right);
	cur->item.print(source);
	displayDesc(source, cur->left);
	return;

}


// Clone Tree
// member 3
void BST :: EmptyClone() { //Ensure SubTree Is Empty

	RemoveSubTreeNodes(root);
	root = NULL;

}

void BST :: RemoveSubTreeNodes(BTNode* cur) { //Remove Nodes From SubTree

	if (cur == NULL) return;

	// Delete the nodes from left and right subtrees

	RemoveSubTreeNodes(cur->left);
	RemoveSubTreeNodes(cur->right);

	// Delete the current node

	delete cur;


}

bool BST::searchItem(BTNode* cur, type item, BTNode*& returnPtr) { //Search Item From Tree

	if (cur == NULL) return false; 

	if (cur->item.compare2(item)) { //search the record by comparing id
		returnPtr = cur;
		return true;
}

	else if (cur->item.compare1(item)) searchItem(cur->left, item, returnPtr);

	else searchItem(cur->right, item, returnPtr);

}

bool BST::CloneSubtree(BST t1, type item) { //Clone SubTree

	//Check Whether Original Tree Is Empty
	if (t1.empty()) {
		cout << "\n\nThe Original Tree Is Empty\n";
		return false;
	}

	BST* t2 = new BST();
	BTNode* t2Root = NULL;

	EmptyClone();

	if (!t1.searchItem(t1.root, item, t2Root)) { // display message if cannot find the record
		cout << "\n\nStudent ID Not Found";
		return false;
	}


	if (!CloneSubTree2(t1, t2, t1.root, item));

}



bool BST::CloneSubTree2(BST t1, BST* t2, BTNode* cur, type item) {

	if (cur == NULL) return false;

	if (cur->item.compare2(item)) {
		CloneSubTree3(t2, cur); //call function to insert clone record to t2
		return true;
	}

	if (cur->item.compare1(item))
		return CloneSubTree2(t1,t2,cur->left, item);

	return CloneSubTree2(t1,t2,cur->right, item);
}


bool BST::CloneSubTree3(BST* t2, BTNode* cur) {
	if (cur == NULL) return false;

	insert(cur->item); // insert to t2
	CloneSubTree3(t2, cur->left);
	CloneSubTree3(t2, cur->right);

}


// Print Level Nodes
//member 4
bool BST::printLevelNodes() {
	if (root == nullptr) return false; // Handle empty tree

	Queue q;
	q.enqueue(root); // Start with the root node

	int level = 0; // Start at the root level

	while (!q.empty()) {
		int levelSize = q.size();  // Nodes at the current level
		cout << "Level " << level << " nodes: ";

		for (int i = 0; i < levelSize; ++i) {
			BTNode* currentNode;
			q.dequeue(currentNode); // Dequeue the current node
			cout << currentNode->item.id << " "; // Print the current node's id

			// Enqueue child nodes for the next level
			if (currentNode->left != nullptr) q.enqueue(currentNode->left);
			if (currentNode->right != nullptr) q.enqueue(currentNode->right);
		}
		cout << endl;
		++level; // Move to the next level
	}
	return true;
}

// Print Paths
bool BST::printPaths() {
	if (root == nullptr) return false; // Handle empty tree
	int path[100];
	cout << "Below are all the external paths for the tree:\n\n";
	printPathsRecur(root, path, 0);
	return true;
}

int BST::printPathsRecur(BTNode* currentNode, int path[], int pathLen) {
	if (currentNode == nullptr)
		return false;

	// Store the current node's id in the path array
	path[pathLen] = currentNode->item.id;
	pathLen++;

	// If it's a leaf node, print the path
	if (currentNode->left == nullptr && currentNode->right == nullptr) {
		printArray(path, pathLen);
	}
	else {
		// Otherwise, continue to explore the left and right subtrees
		printPathsRecur(currentNode->left, path, pathLen);
		printPathsRecur(currentNode->right, path, pathLen);
	}
	return true;
}

void BST::printArray(int path[], int length) {
	for (int i = 0; i < length; ++i) {
		cout << path[i] << " ";
	}
	cout << endl;
}