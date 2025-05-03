/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
class Queue {
    int *queue;
    int queueSize;
    int head;
    int tail;
    int numEle;
public:
    bool enque(int val);
    bool deque(int *val);
    bool isEmpty();
    bool isFull();
    Queue(int size);
    int numElements();
};

Queue::Queue(int size) {
    queue = (int *) malloc(sizeof(int) * size);
    queueSize = size;
    numEle = 0;
    head = tail = 0;
}

bool Queue::enque(int val) {
    if(isFull()) {
        return false;
    }
    queue[head++%queueSize] = val;
    numEle++;
    return true;
}

bool Queue::deque(int *val) {
    if(isEmpty()) {
        return false;
    }
    numEle--;
    *val = queue[tail++%queueSize];
    return true;
}

bool Queue::isEmpty() {
    return numEle == 0;
}

bool Queue::isFull() {
    return queueSize == numEle;
}

int Queue::numElements() {
    return numEle;
}

int main()
{
    Queue que(5);
    int val;
    que.enque(1);
    que.enque(2);
    que.enque(3);
    que.enque(4);
    que.deque(&val);
    que.deque(&val);
    que.enque(5);
    que.enque(6);
    que.enque(7);
    que.deque(&val);
    que.deque(&val);
    que.deque(&val);
    que.deque(&val);
    std::cout << "num:" << que.numElements() << std::endl;
    if(que.deque(&val)) {
        std::cout<< val;
    }

    return 0;
}
