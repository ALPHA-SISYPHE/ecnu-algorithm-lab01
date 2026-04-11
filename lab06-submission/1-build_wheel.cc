#include <iostream>
#include <string>

using namespace std;

struct Task
{
    string name;
    int time;
};

struct cqueue
{
    Task *data;
    int head;
    int tail;
    int size;
};

cqueue *create(int n)
{
    cqueue *q = new cqueue;
    q->data = new Task[n];
    q->head = 0; // 队首位置，待删除
    q->tail = 0; // 空位置，待插入
    q->size = n;
    return q;
}

void init_queue(cqueue *q, Task t)
{
    q->data[q->tail] = t;
    q->tail = (q->tail + 1) % q->size;
}

void enqueue(cqueue *q, Task t)
{
    q->data[q->tail] = t;
    q->tail = (q->tail + 1) % q->size;
}

void dequeue(cqueue *q)
{
    q->head = (q->head + 1) % q->size;
}

int main()
{

    // 加速IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;
    cqueue *tsks = create(N + 1);
    for (int i = 0; i < N; i++)
    {
        Task t;
        cin >> t.name >> t.time;
        init_queue(tsks, t);
    }

    int time = 0;
    // 条件判断：队列不为空
    while (tsks->head != tsks->tail)
    {
        // 搞个指针指向首元素
        Task *operate = &tsks->data[tsks->head];
        dequeue(tsks);
        if (operate->time <= K)
        {
            time += operate->time;
            cout << operate->name << " " << time << endl;
        }
        else
        {
            operate->time -= K;
            time += K;
            enqueue(tsks, *operate);
        }
    }
}