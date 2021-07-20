#include <iostream>
//using namespace std;

using std::cout;
using std::cin;
using std::endl;

class node
{
	node *pPrev;
	int iData;
	node *pNext;
	
public:
	node();
	~node();
	
	friend class list;
};

class list
{
	node *pFirst;
	node *pLast;
	
public:
	list();
	
	int IsEmpty();
	
	void InsertFirst(int);
	void InsertLast(int);
	void InsertAtPosition(int, int);
	
	int DeleteFirst();
	int DeleteLast();
	int DeleteAtPosition(int);
	
	int SearchFirstOccurance(int);
	int SearchLastOccurance(int);
	int SearchAllOccurance(int);
	
	int CountNode();
	
	void Display();
	
	~list();
};

int main()
{
	list lObj;
	int iPos;
	int iData;
	int iTemp;
	int iChoice;

	while(1)
	{
		cout << "\n1.Insert\n2.Delete\n3.Search\n4.Count\n5.Exit\n";
		cout << "Enter your choice:\t";
		cin >> iChoice;
		
		if(iChoice <= 0 || iChoice > 8)
		{
			cout << "Enter valid choice.\n";
			continue;
		}

		switch(iChoice)
		{
			case 1:	while(1)
				{
					cout << "\n1.InsertFirst\n2.InsertLast\n3.InsertAtPosition\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;

					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}

					if(3 == iChoice)
					{
						cout << "\nEnter the position:\t";
						cin >> iPos;
						
						if(iPos <= 0 || iPos > (lObj.CountNode() + 1))
						{
							cout << "Enter valid position.\n";
							continue;
						}
					}

					cout << "Enter data to be inserted:\t";
					cin >> iData;

					switch(iChoice)
					{
						case 1:	lObj.InsertFirst(iData);
							break;
						
						case 2: lObj.InsertLast(iData);
							break;
	
						case 3: lObj.InsertAtPosition(iData, iPos);
					}			

					lObj.Display();
				}break;
				
			case 2: if(lObj.IsEmpty())
				{
					cout << "Linked List Empty, Deletion Not Possible.\n";
					break;
				}
		
				while(1)
				{
					cout << "\n1.DeleteFirst\n2.DeleteLast\n3.DeleteAtPosition\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;

					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}

					switch(iChoice)
					{
						case 1: iData = lObj.DeleteFirst();
							break;

						case 2: iData = lObj.DeleteLast();
							break;

						case 3: if(lObj.IsEmpty())
							{
								cout << "Linked List is Empty\n";
								continue;
							}
								
							cout << "\nEnter the position:\t";
							cin >> iPos;
						
							if(iPos <= 0 || iPos > lObj.CountNode())
							{
								cout << "Enter valid position.\n";
								continue;
							}
							iData = lObj.DeleteAtPosition(iPos);
					}

					if(-1 != iData)
						cout << "\nDeleted data is " << iData << endl;

					lObj.Display();
				}break;

			case 3:	if(lObj.IsEmpty())
				{
					cout << "Linked List Empty, Searching Not Possible.\n";
					break;
				}

				while(1)
				{
					cout << "\n1.SearchFirstOccurance\n2.SearchLastOccurance\n3.SearchAllOccurance\n4.Back\n";
					cout << "Enter your choice:\t";
					cin >> iChoice;
				
					if(4 == iChoice)
						break;

					if(iChoice <= 0 || iChoice > 4)
					{
						cout << "Enter valid choice.\n";
						continue;
					}
					lObj.Display();

					cout << "Enter data to search:\t";
					cin >> iData;

					switch(iChoice)
					{
						case 1: iPos = lObj.SearchFirstOccurance(iData);
							if(-1 == iPos)
								cout << "Linked List is Empty\n";
							else if(0 != iPos)	
								cout << iData << " is found at "<< iPos << " location " << endl;

							else
								cout << "Data not Found\n";

							break;

						case 2: iPos = lObj.SearchLastOccurance(iData);
							if(-1 == iPos)
								cout << "Linked List is Empty\n";
							else if(0 != iPos)	
								cout << iData << " is found at "<< iPos << " location" << endl;
							else
								cout << "Data not Found\n";
							break;

						case 3: iPos = lObj.SearchAllOccurance(iData);
							cout << iData << " is found " << iPos << " time.\n";
					}
				}break;

			case 4: cout << "Total nodes present : " << lObj.CountNode() << endl;
				break;

			case 5: lObj.~list();
				cout <<"Bye...\n";
				lObj.Display();
				return 0;
		}
	}
}

node :: node()
{
	iData = 0;
	pPrev = pNext = NULL;
}

node :: ~node()
{
	if(pNext != NULL && pPrev != NULL)
	{
		delete pNext;
		delete pPrev;
		pNext = pPrev = NULL;	
	}
}

list :: list()
{
	pFirst = pLast = NULL;
}

list :: ~list()
{ 
	if(NULL == pFirst)
		return;

	while(pFirst != pLast)
	{
		pFirst->pPrev = NULL;
		pFirst = pFirst->pNext;
		pLast->pNext->pNext = NULL;
		delete pLast->pNext;

		pLast->pNext = pFirst;
	}

	pFirst->pNext = NULL;
	pFirst->pPrev = NULL;
	delete pFirst;

	pFirst = NULL;
	pLast = NULL;
	
	cout << "\nAll Nodes Deleted Successfully\n";
	Display();
}

void list :: InsertFirst(int iData)
{
	node *pNewNode = NULL;
	
	pNewNode = new node;

	if(NULL != pNewNode)
	{	
		cout << "Memory allocation failed\n";
		return;
	}

	pNewNode->iData = iData;

	if(NULL == pFirst)
	{
		pFirst = pLast = pNewNode;
		pLast->pNext = pFirst;
		pFirst->pPrev = pLast;
		return;
	}

	pNewNode->pNext = pFirst;
	pFirst->pPrev = pNewNode;
	pFirst = pNewNode;
	pLast->pNext = pFirst;
	pFirst->pPrev = pLast;
}

void list :: InsertLast(int iData)
{
	node *pNewNode = NULL;

	pNewNode = new node;

	if(NULL == pNewNode)
	{
		cout << "Memory allocation failed\n";
		return;
	}
	
	pNewNode->iData = iData;

	if(NULL == pFirst)
	{
		pFirst = pLast = pNewNode;
		pLast->pNext = pFirst;
		pFirst->pPrev = pLast;
		return;
	}

	pLast->pNext = pNewNode;
	pNewNode->pPrev = pLast;
	pLast = pNewNode;
	pLast->pNext = pFirst;
	pFirst->pPrev = pLast;
}

void list :: InsertAtPosition(int iNo, int iPos)
{
	int iCount;
	node *pTemp = NULL;
	node *pNewNode = NULL;

	iCount = CountNode();

	if(1 == iPos)
	{
		InsertFirst(iNo);
		return;
	}

	if(iPos == iCount + 1)
	{
		InsertLast(iNo);
		return;
	}

	pTemp = pFirst;
	iCount = 1;

	while(iCount < iPos - 1)
	{
		iCount++;
		pTemp = pTemp->pNext;
	}

	pNewNode = new node;
	if(NULL == pNewNode)
	{
		cout << "Memory allocation Failed\n";
		return;
	}

	pNewNode->iData = iNo;

	pNewNode->pNext = pTemp->pNext;
	pTemp->pNext->pPrev = pNewNode;
	pTemp->pNext = pNewNode;
	pNewNode->pPrev = pTemp;
}

int list :: DeleteFirst()
{
	int iDelData;

	if(NULL == pFirst)
		return -1;

	iDelData = pFirst->iData;	
	
	if(pFirst == pLast)			// single node
	{
		pFirst->pPrev = NULL;
		pFirst->pNext = NULL;
		delete pFirst;
		pFirst = pLast = NULL;
		return iDelData;
	}

	pFirst = pFirst->pNext;
	pLast->pNext->pPrev = NULL;			//First node ka pPrev NULL kiya
	pLast->pNext->pNext = NULL;			//First node ka pNext NULL kiya

	delete pLast->pNext;
	pFirst->pPrev = pLast;
	pLast->pNext = pFirst;
	
	return iDelData;
}

int list :: DeleteLast()
{
	int iDelData;

	if(NULL == pFirst)	
		return -1;

	if(pFirst == pLast)
	{
		pFirst->pPrev = NULL;
		iDelData = pFirst->iData;
		pFirst->pNext = NULL;
		delete pFirst;
		pFirst = pLast = NULL;
		return iDelData;
	}

	pLast = pLast->pPrev;
	pLast->pNext->pPrev = NULL;
	iDelData = pLast->pNext->iData;
	pLast->pNext->pNext = NULL;

	delete pLast->pNext;
	pFirst->pPrev = pLast;
	pLast->pNext = pFirst;
	return iDelData;
}

int list :: DeleteAtPosition(int iPos)
{
	int iValue;
	node *pTemp = NULL;

	if(NULL == pFirst)
		return -1;

	if(1 == iPos)
		return DeleteFirst();

	if(iPos == CountNode())
		return DeleteLast();
	
	pTemp = pFirst;
	iValue = 1;
	
	while(iValue < iPos)
	{
		iValue++;
		pTemp = pTemp->pNext;
	}
	
	pTemp->pPrev->pNext = pTemp->pNext;
	pTemp->pNext->pPrev = pTemp->pPrev;
	pTemp->pPrev = NULL;
	pTemp->pNext = NULL;

	iValue = pTemp->iData;
	delete pTemp;

	return iValue;   	
}

int list :: SearchFirstOccurance(int iKey)
{
	int iCount = 1;
	node *pTemp = pFirst;

	if(NULL == pFirst)
		return -1;

	do
	{
		if(pTemp->iData == iKey)
			break;
		iCount++;		
		pTemp = pTemp->pNext;
	}while(pTemp != pLast->pNext);

	if(pTemp == pLast->pNext && iCount != 1)
		iCount = 0;

	return iCount;
}

int list :: SearchLastOccurance(int iKey)
{
	int iCount = 0;
	int iLast = 0;
	node *pTemp = pFirst;
	
	if(NULL == pFirst)
		return -1;

	do
	{
		iCount++;	
		if(pTemp->iData == iKey)
			iLast = iCount;

		pTemp = pTemp->pNext;
	}while(pTemp != pLast->pNext);

	return iLast;
}

int list :: SearchAllOccurance(int iKey)
{
	int iCount = 0;
	node *pTemp = pFirst;
	
	if(NULL == pFirst)
		return -1;

	do
	{
		if(pTemp->iData == iKey)
			iCount++;

		pTemp = pTemp->pNext;
	}while(pTemp != pLast->pNext);
	
	return iCount;
}

void list :: Display()
{
	node *pTemp = pFirst;
	
	if(NULL == pTemp)
	{
		cout << "\nLinked List is Empty!!!\n";
		return;
	}

	cout << "\nLinked List is:\n";
	do
	{
		cout << "<-|" << pTemp->iData << "|->";
		pTemp = pTemp->pNext;
	}while(pTemp != pLast->pNext);
	cout << "\n";
}

int list :: CountNode()
{
	int iCount = 0;
	node *pHead = pFirst;
	
	if(NULL == pHead)
		return iCount;
	do
	{
		iCount++;
		pHead = pHead->pNext;	
	}while(pHead != pLast->pNext);

	return iCount;
}

int list :: IsEmpty()
{
	if(NULL == pFirst)
		return 1;
	return 0;
}
