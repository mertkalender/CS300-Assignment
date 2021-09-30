//MERT KALENDER - 26351

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include "BST.h"


using namespace std;


int getUserInput(){			// To get input from user

	cout << "Input: ";
	int n;
	cin >> n;
	return n;
}

void displayMenu() {		//Displays menu
	cout << "MENU" << endl << "Please enter an input between [1 - 6]: " << endl << "1- Display the sections [AVL]" << endl
		<< "2- Display the sections [BST]" << endl << "3- Select a section" << endl << "4- Add new section" << endl << "5- Delete a section" << endl << "6- Exit" << endl;
}

void displaySectionMenu() {
	cout << "Please enter an input between [1 - 7]: " << endl << "1- Display the items [AVL]" << endl << "2- Display the items [BST]" << endl
		<< "3- Display the information of a item" << endl << "4- Add new item" << endl << "5- Update the information of a item" << endl
		<< "6- Delete an item" << endl << "7- Return to main menu" << endl;
}



int main(){

	cout << "Welcome to the the Notes" << endl << endl;

	fstream in;
	string fname = "data.txt", s;

	const Item ITEM_NOT_FOUND("","");
	BinarySearchTree<Item> ItemBST(ITEM_NOT_FOUND);
	AVLTree<Item> ItemAVL(ITEM_NOT_FOUND);
	
	BinarySearchTree<Item>* BSTptr = &ItemBST;
	AVLTree<Item>* AVLptr = &ItemAVL;

	const Section SECTION_NOT_FOUND("", BSTptr, AVLptr);
	BinarySearchTree<Section> BSTNotebook(SECTION_NOT_FOUND);
	AVLTree<Section> AVLNotebook(SECTION_NOT_FOUND);


	in.open(fname.c_str());
	string activeSectionName;
	while (getline(in, s)) {
		

		if (s[0] != '-') {
			
			Item ITEM_NOT_FOUND("", "");

			BinarySearchTree<Item> EmptyBST(ITEM_NOT_FOUND);
			BinarySearchTree<Item>* BSTptr = &EmptyBST;

			AVLTree<Item> EmptyAVL(ITEM_NOT_FOUND);
			AVLTree<Item>* AVLptr = &EmptyAVL;

			activeSectionName = s;
			Section new_section(s, BSTptr, AVLptr);
			
			auto start_AVL = std::chrono::high_resolution_clock::now();
			AVLNotebook.insert(new_section);
			auto end_AVL = std::chrono::high_resolution_clock::now();
			long long timer_AVL = (end_AVL - start_AVL).count() / 1000.0;
			cout << "Section \"" << activeSectionName << "\" has been inserted into the AVL notebook." << endl;
			cout << "[AVL] Elapsed time :" << timer_AVL << " microseconds" << endl;

			auto start_BST = std::chrono::high_resolution_clock::now();
			BSTNotebook.insert(new_section);
			auto end_BST = std::chrono::high_resolution_clock::now();
			long long timer_BST = (end_BST - start_BST).count() / 1000.0;
			cout << "Section \"" << activeSectionName << "\" has been inserted into the BST notebook." << endl;
			cout << "[BST] Elapsed time :" << timer_BST << " microseconds" << endl << endl;
		}
		else {
			string title, info;

			size_t pos_t = (int) (s.find("-",1));
			info = s.substr(pos_t+1);
			title = s.substr(1, pos_t);


			Item new_item(title, info);
			Section activeSection(activeSectionName, NULL, NULL);

			Section sectionToProcess = BSTNotebook.find(activeSection);

			//sectionToProcess.getSectionBST()->insert(new_item); //Stack overflow verip butun kodu bozuyor. Neredeyse her sey mukemmel calistigi icin
			//sectionToProcess.getSectionAVL()->insert(new_item);									commentleyip o sekilde submitledim.

		}
	}
	in.close();

	displayMenu();
	int x = getUserInput();
	while (x != 6) {

		switch (x){

			case 1: {  //Print AVLTree
				AVLNotebook.printTree();
				x = getUserInput();
				break;
			}
			case 2: {	//Print BST
				BSTNotebook.printTree();
				x = getUserInput();
				break;
			}
			case 3: {		//Pick a section to process
				bool showmenu = false;
				string input;
				cout << "Enter the title of the section: ";
				cin >> input;
				Section inputSection(input, NULL, NULL);
				if (AVLNotebook.found(inputSection)) {  //Search for given section if it exists
					
					showmenu = true;
					Section sectionToProcess = AVLNotebook.find(inputSection);
					cout << endl << "Selected section -> " << sectionToProcess << endl;
					displaySectionMenu();
					int sectionInput = getUserInput();

					while (sectionInput != 7) {
						switch (sectionInput)
						{
							case 1: {  //Print AVL Tree of selected section

								sectionToProcess.getSectionAVL()->printTree();
								sectionInput = getUserInput();
								break;
							}
							case 2: {	//Print BST of selected section

								sectionToProcess.getSectionBST()->printTree();
								sectionInput = getUserInput();
								break;
							}
							case 3: {   //Print info of the selected item in section

								string itemName;
								cout << "Enter the title of the item: ";
								cin >> itemName;

								Item itemToSearch(itemName, "");

								auto start_AVL = std::chrono::high_resolution_clock::now();
								sectionToProcess.getSectionAVL()->found(itemToSearch);
								auto end_AVL = std::chrono::high_resolution_clock::now();
								long long timer_AVL = (end_AVL - start_AVL).count() / 1000.0;
								cout << "[AVL] Elapsed time :" << timer_AVL << " microseconds" << endl;

								auto start_BST = std::chrono::high_resolution_clock::now();
								sectionToProcess.getSectionBST()->found(itemToSearch);
								auto end_BST = std::chrono::high_resolution_clock::now();
								long long timer_BST = (end_BST - start_BST).count() / 1000.0;
								cout << "[BST] Elapsed time :" << timer_BST << " microseconds" << endl;


								if (sectionToProcess.getSectionBST()->found(itemToSearch)) {  //Item exists in the Section

									Item foundItem = sectionToProcess.getSectionBST()->find(itemToSearch);
									
									sectionToProcess.getSectionAVL()->find(itemToSearch);

									cout << foundItem.getInfo() << endl;
								}
								else {
									cout << "Invalid title." << endl;
								}

								sectionInput = getUserInput();
								break;
							}
							case 4: {  //Insert new item

								string itemName, itemInfo;
								cout << "Enter a title for the item: ";
								cin >> itemName;

								Item itemToCheck(itemName, "");

								if (sectionToProcess.getSectionBST()->found(itemToCheck)) {  // If item already exists
									cout << "Item \"" << itemName << "\" already exists in the \"" << sectionToProcess.getTitle() << "\"." << endl;
									
								}
								else {
									cout << "Enter a description for the item: ";
									cin >> itemInfo;

									Item newItem(itemName, itemInfo);

									auto start_AVL = std::chrono::high_resolution_clock::now();
									sectionToProcess.getSectionAVL()->insert(newItem);
									auto end_AVL = std::chrono::high_resolution_clock::now();
									long long timer_AVL = (end_AVL - start_AVL).count() / 1000.0;
									cout << "[AVL] Elapsed time :" << timer_AVL << " microseconds" << endl;
									
									auto start_BST = std::chrono::high_resolution_clock::now();
									sectionToProcess.getSectionBST()->insert(newItem);
									auto end_BST = std::chrono::high_resolution_clock::now();
									long long timer_BST = (end_BST - start_BST).count() / 1000.0;
									cout << "[BST] Elapsed time :" << timer_BST << " microseconds" << endl;

									cout << "The new item \"" << itemName << "\" has been inserted." << endl;
								}

								sectionInput = getUserInput();
								break;
							}
							case 5: {  //Update info of an item
								
								string itemName;
								cout << "Enter the title of the item: ";
								cin >> itemName;
								Item itemToSearch(itemName, "");

								auto start_AVL = std::chrono::high_resolution_clock::now();
								sectionToProcess.getSectionAVL()->found(itemToSearch);
								auto end_AVL = std::chrono::high_resolution_clock::now();
								long long timer_AVL = (end_AVL - start_AVL).count() / 1000.0;
								cout << "[AVL] Elapsed time :" << timer_AVL << " microseconds" << endl;
								
								auto start_BST = std::chrono::high_resolution_clock::now();
								sectionToProcess.getSectionBST()->found(itemToSearch);
								auto end_BST = std::chrono::high_resolution_clock::now();
								long long timer_BST = (end_BST - start_BST).count() / 1000.0;
								cout << "[BST] Elapsed time :" << timer_BST << " microseconds" << endl;

								if (sectionToProcess.getSectionBST()->found(itemToSearch)) { //Search for item whether it exists or not.
									
									Item foundItem = sectionToProcess.getSectionBST()->find(itemToSearch);

									string new_info;
									cout << "Enter the new information: ";
									cin >> new_info;
									foundItem.setInfo(new_info);
								}
								else {  //Item does not exist in the given section
									cout << "Item \"" << itemName << "\" does not exist in the \"" << sectionToProcess.getTitle() << "\"." << endl;
								}

								sectionInput = getUserInput();
								break;
							}
							case 6: {	//Delete an item
								
								string itemName;
								cout << "Enter the title of the item: ";
								cin >> itemName;

								Item itemToSearch(itemName, "");
								if (sectionToProcess.getSectionBST()->found(itemToSearch)) { //Item exists in the given section
									
									auto start_AVL = std::chrono::high_resolution_clock::now();
									sectionToProcess.getSectionAVL()->remove(itemToSearch);
									auto end_AVL = std::chrono::high_resolution_clock::now();
									long long timer_AVL = (end_AVL - start_AVL).count() / 1000.0;
									cout << "[AVL] Elapsed time :" << timer_AVL << " microseconds" << endl;
									
									auto start_BST = std::chrono::high_resolution_clock::now();
									sectionToProcess.getSectionBST()->remove(itemToSearch);
									auto end_BST = std::chrono::high_resolution_clock::now();
									long long timer_BST = (end_BST - start_BST).count() / 1000.0;
									cout << "[BST] Elapsed time :" << timer_BST << " microseconds" << endl;


									cout << "The item \"" << itemName << "\" has been deleted." << endl;
								}
								else {		//Item does not exist in the given section
									cout << "Item \"" << itemName << "\" does not exist in the \"" << sectionToProcess.getTitle() << "\"." << endl;
								}


								sectionInput = getUserInput();
								break;
							}
						}
					}
				}
				else {
					cout << "Invalid title!" << endl << endl;
				}

				if (showmenu) {
					displayMenu();
				}

				x = getUserInput();
				break;
			}
			case 4: {		//Add new section

				string newSectionName;
				cout << "Enter a title for the section: ";
				cin >> newSectionName;


				Item ITEM_NOT_FOUND("", "");

				BinarySearchTree<Item> EmptyBST(ITEM_NOT_FOUND);
				BinarySearchTree<Item>* BSTptr = &EmptyBST;

				AVLTree<Item> EmptyAVL(ITEM_NOT_FOUND);
				AVLTree<Item>* AVLptr = &EmptyAVL;


				Section newSection(newSectionName, BSTptr, AVLptr);

				if (BSTNotebook.found(newSection)) {								//Section already exists

					cout << "Section \"" << newSectionName << "\" already exists." << endl;
				}

				else {
					BSTNotebook.insert(newSection);
					AVLNotebook.insert(newSection);

					cout << "The new section \"" << newSectionName << "\" has been inserted." << endl;
				}

				x = getUserInput();
				break;
			}
			case 5: {

				string sectionName;
				cout << "Enter the title of the section: ";
				cin >> sectionName;

				Section sectionToSearch(sectionName, NULL, NULL);

				if (!BSTNotebook.found(sectionToSearch)) {		//Section to be removed does not exist

					cout << "Section \"" << sectionName << "\" does not exist." << endl;
				}
				else {

					BSTNotebook.remove(BSTNotebook.find(sectionToSearch));
					AVLNotebook.remove(AVLNotebook.find(sectionToSearch));
					cout << "The section has been deleted." << endl;

				}

				x = getUserInput();
				break;
			}
		}
	}

}