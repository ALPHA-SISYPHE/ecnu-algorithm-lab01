#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream> // 文件输出

using namespace std;

// 维护小组的状态结构体
struct Team
{
    int id;           // 小组编号 (0, 1, 2)
    bool is_busy;     // 当前是否在忙小组干完活的时间
    int current_task; // 正在处理的仓库号
    int busy_until;   // 预计完成的绝对时间点（）
};

// 核心模拟器函数
void simulate(const string &tree_name, int n, const vector<int> &parent, const vector<int> &duration, ofstream &out_file)
{
    cout << "=== " << tree_name << " 仓储停运模拟开始 ===" << "\n";
    out_file << "=== " << tree_name << " 仓储停运模拟开始 ===" << "\n";

    // 统计每个节点有几个下级 (入度)
    vector<int> pending_children(n + 1, 0);
    for (int i = 2; i <= n; i++)
    {
        pending_children[parent[i]]++;
    }

    // 准备就绪队列 (使用优先队列，保证编号小的优先处理，使输出更稳定、有序)
    priority_queue<int, vector<int>, greater<int>> ready_queue;

    // 初始状态：把所有没有下级的叶子节点（pending_children 为 0）加入就绪队列
    for (int i = 1; i <= n; i++)
    {
        if (pending_children[i] == 0)
        {
            ready_queue.push(i);
        }
    }

    // 初始化 3 个维护小组
    vector<Team> teams(3);
    for (int i = 0; i < 3; i++)
    {
        teams[i] = {i, false, 0, 0};
    }

    int current_time = 0; // 当前时间
    int completed_count = 0;// 完成的仓库数量,用于循环控制

    // 只要还有仓库没关停完，时间循环就继续
    while (completed_count < n)
    {

        // 步骤 1：检查当前时间 current_time，是否有小组刚好完工
        for (int i = 0; i < 3; i++)
        {
            if (teams[i].is_busy && teams[i].busy_until == current_time)
            {
                int finished_task = teams[i].current_task;
                cout << "[t=" << current_time << "] Team " << teams[i].id
                     << " 完成仓库 " << finished_task << " 的停运\n";
                out_file << "[t=" << current_time << "] Team " << teams[i].id
                     << " 完成仓库 " << finished_task << " 的停运\n";

                teams[i].is_busy = false; // 小组重新空闲
                completed_count++;

                // 重点：通知这个仓库的直属上级，它的一个下级搞定了！
                int p = parent[finished_task];
                if (p != 0)
                {                          // 根节点的parent是 0，代表没有上级，所以不用通知
                    pending_children[p]--; // 给上级的「待完成下级计数器」-1
                    // 如果直属上级的所有下级都搞定了，上级进入就绪队列
                    if (pending_children[p] == 0)
                    {
                        ready_queue.push(p);
                    }
                }
            }
        }

        // 步骤 2：如果有空闲小组，且有可以开工的仓库，赶紧分配任务
        for (int i = 0; i < 3; i++)
        { // 循环检查3个小组
            if (!teams[i].is_busy && !ready_queue.empty())
            { // 这个小组现在是空闲的，没在干活;就绪队列里还有仓库在等着被修（有活干）
                int task = ready_queue.top();
                ready_queue.pop();

                teams[i].is_busy = true; /*把小组状态改成 正在干活
                                            这样下一个时间点就不会再给它派活了*/
                teams[i].current_task = task;
                teams[i].busy_until = current_time + duration[task];

                cout << "[t=" << current_time << "] Team " << teams[i].id
                     << " 开始停运仓库 " << task
                     << ", 预计完成时间 t=" << teams[i].busy_until << "\n";
                out_file << "[t=" << current_time << "] Team " << teams[i].id
                     << " 开始停运仓库 " << task
                     << ", 预计完成时间 t=" << teams[i].busy_until << "\n";
            }
        }

        // 步骤 3：任务分配完毕，让时间快进 (Fast-Forward)
        // 找到下一个最近的完工时间，直接把 current_time 跳过去，避免死循环一秒一秒地数
        if (completed_count == n)
            break; // 全部完成就退出

        int next_event_time = 1e9; // 设一个无限大
        for (int i = 0; i < 3; i++)
        {
            if (teams[i].is_busy)
            {
                next_event_time = min(next_event_time, teams[i].busy_until);
            }
        }

        // 快进时间
        if (next_event_time != 1e9)
        {
            current_time = next_event_time;// 直接跳到最近的完工时间，直接迭代太慢了
        }
    }

    cout << "总完成时间: " << current_time << "\n\n";
    out_file << "总完成时间: " << current_time << "\n\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream log_file("warehouse_shutdown_log.txt");
    if (!log_file.is_open())
    {
        cerr << "错误：无法创建/打开日志文件！请检查程序权限" << endl;
        return 1;
    }

    int n = 12;
    // 仓库 1 到 12 的关停所需时间 (下标 0 占位不用)
    vector<int> duration = {0, 7, 3, 4, 2, 2, 1, 3, 2, 1, 1, 2, 1};

    // 存储每种树形结构的父节点关系 (parent[i] 表示节点 i 的直属上级)
    // 记录每个索引值对应的父节点
    vector<int> parent_chain(n + 1, 0);
    vector<int> parent_star(n + 1, 0);
    vector<int> parent_binary(n + 1, 0);

    // 1. 构建链式树: 1 -> 2 -> 3 -> ... -> 12
    for (int i = 2; i <= n; i++)
    {
        parent_chain[i] = i - 1;
    }

    // 2. 构建星型树: 1 是总根，其他所有节点都直接连在 1 下面
    for (int i = 2; i <= n; i++)
    {
        parent_star[i] = 1;
    }

    // 3. 构建平衡二叉树: 利用数组下标性质，节点 i 的父节点是 i / 2 (整除)
    // 例如：2和3的父节点是1，4和5的父节点是2...
    for (int i = 2; i <= n; i++)
    {
        parent_binary[i] = i / 2;
    }

    // 分别运行三种情况的模拟
    simulate("链式结构", n, parent_chain, duration, log_file);
    simulate("星型结构", n, parent_star, duration, log_file);
    simulate("平衡二叉树", n, parent_binary, duration, log_file);


    log_file.close();

    cout << "✅ 模拟完成！所有日志已同步保存到 warehouse_shutdown_log.txt 文件" << endl;

    return 0;
}