// Алгоритмы поиска в ширину и глубину.
//
// 7. Определить, существует ли маршрут между двумя заданными вершинами в неориентированном графе. 
// Граф в памяти представлять в виде матрицы.
// 
// Обход в глубину.
// Выполнили: Пятанин А., Коржов К., Ишутин М., Бурлаков В. (ПМ-93)
// Автор: Бурлаков В.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <queue>

std::vector<bool> marks;

void doBfs(size_t source, const std::vector<std::vector<size_t>> &graph)
{
   std::queue<size_t> q;
   q.push(source);

   while (!q.empty())
   {
      size_t curr = q.front();
      q.pop();

      marks[curr] = true;
      for (size_t i = 0; i < graph[curr].size(); i++)
      {
         if (!marks[graph[curr][i]])
            q.push(graph[curr][i]);
      }
   }
}

int main()
{
   std::ifstream in("input.txt");
   std::ofstream out("output.txt");

   std::ios::sync_with_stdio(false);
   std::cin.tie(NULL);

   size_t n = 0;
   in >> n;
   std::vector<std::vector<size_t>> graph(n, std::vector<size_t>(n, -1));

   for (size_t i = 0; i < n; i++)
   {
      for (size_t j = 0; j < n; j++)
      {
         size_t weight = 0;
         in >> weight;
         graph[i][j] = weight;
         graph[j][i] = weight;
      }
   }

   size_t source = 0, destination = 0;
   in >> source >> destination;

   marks.assign(n, false);

   auto startTime = std::chrono::high_resolution_clock::now();

   doBfs(source - 1, graph);

   auto endTime = std::chrono::high_resolution_clock::now() - startTime;
   auto elapsedTime = std::chrono::duration<double>(endTime).count();

   if (!marks[destination - 1])
      out << "Route does NOT exist.\n";
   else
      out << "Route exists.\n";

   out << "Algorithm time is " << elapsedTime << " seconds.\n";

   return 0;
}
