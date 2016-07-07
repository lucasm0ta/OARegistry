template <class ItemType>
class CosequentialProcess
{
public:
    virtual int initializeList(int listNumber, char* listName) = 0;
    virtual int initializeOutput(char* outputListName) = 0;
    virtual ItemType item(int listNumber) = 0;
    virtual int processItem(int listNumber) = 0;
    virtual int finishUp() = 0;
    virtual int match2Lists(char* list1Name, char* list2Name, char* outputListName);
}
int CosequentialProcess<ItemType>::merge2Lists (char* list1, char* list2)
{
    int moreItems1, moreItems2;
    initializeList(1,list1Name);
    initializeList(2,list2Name);
    initializeOutput(outputListName);

    while (moreItems1 || moreItems2) {
        if (item(1) < item(2)) {
            processItem(1);
            moreItems1 = nextItemInList(1);
        } else if (item(1) == item(2)) {
            processItem(1);
            moreItems1 = nextItemInList(1);
            moreItems2 = nextItemInList(2);
        } else {
            processItem(2);
            moreItems2 = nextItemInList(2);
        }
    }
    finishUp();
    return 1;
}

class StringListProcess : public CosequentialProcess<String&>
{
public:
    StringListProcess(int numberOfLists);
    int initializeList(int listNumber, char* listName) = 0;
    int initializeOutput(char* outputListName) = 0;
    String& item(int listNumber) = 0;
    int processItem(int listNumber) = 0;
    int finishUp() = 0;
    int match2Lists(char* list1Name, char* list2Name, char* outputListName);
}

int match (char* listName, char* list2Name, char* outputListName) {
    int moreItems;
    initializeList(1,listName);
    initializeList(2,list2Name);
    initializeOutput(outputListNamer);
    moreItems = nextItemInList(1) && nextItemInList(2);
    while (moreItems) {
        if (item(1) < item(2)) {
            moreItems = nextItemInList(1);
        } else if (item(1) == item(2)) {
            processItem(1);
            moreItems = nextItemInList(1) && nextItemInList(2);
        } else {
            moreItems = nextItemInList(2);
        }
    }
    finishUp();
    return 1;
}
