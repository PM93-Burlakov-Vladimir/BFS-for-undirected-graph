// Алгоритмы поиска в ширину и глубину.
//
// 7. Определить, существует ли маршрут между двумя заданными вершинами в неориентированном графе. 
// Граф в памяти представлять в виде матрицы.
// 
// Обход в ширину.
// Выполнили: Пятанин А., Коржов К., Ишутин М., Бурлаков В. (ПМ-93)
// Автор: Бурлаков В.
// Рефакторинг: Коржов К.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <queue>

bool doBfs( size_t startVertex, size_t targetVertex , const std::vector<std::vector<size_t>> &graph )
{
   std::vector<bool> marks(graph[0].size(), false);
   marks[startVertex] = true;

   std::queue<size_t> q;
   q.push(startVertex);

   while (!q.empty())
   {
      size_t iVertex = q.front();
      q.pop();

      for (size_t jVertex = 0; jVertex < graph[iVertex].size(); jVertex++)
      {
         if (!marks[jVertex] && graph[iVertex][jVertex])
         {
            q.push(jVertex);
            marks[jVertex] = true;
         }
      }
      if (marks[targetVertex])
         return true;
   }

   return false;
}

int main()
{
   std::ios::sync_with_stdio(false);

   std::ifstream in("input.txt");
   std::ofstream out("output.txt");

   size_t vertexCount = 0;
   in >> vertexCount;
   std::vector<std::vector<size_t>> graph(vertexCount, std::vector<size_t>(vertexCount, -1));

   for (size_t iVertex = 0; iVertex < vertexCount; iVertex++)
      for (size_t jVertex = 0; jVertex < vertexCount; jVertex++)
         in >> graph[iVertex][jVertex];

   size_t startVertex = 0, targetVertex = 0;
   in >> startVertex >> targetVertex;
   startVertex--;
   targetVertex--;

   auto startTime = std::chrono::high_resolution_clock::now();

   bool routeFound = doBfs(startVertex, targetVertex, graph);

   auto endTime = std::chrono::high_resolution_clock::now() - startTime;
   auto elapsedTime = std::chrono::duration<double>(endTime).count();

   if (routeFound)
      out << "Route exists.\n";
   else
      out << "Route does NOT exist.\n";

   out << "Algorithm time is " << elapsedTime << " seconds.\n";

   return 0;
}
