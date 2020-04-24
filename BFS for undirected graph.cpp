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

std::vector<bool> g_Marks = {false};

void doBfs( size_t sourceVertex, size_t destinationVertex , const std::vector<std::vector<size_t>> &graph )
{
   std::queue<size_t> q;
   q.push(sourceVertex);

   while (!q.empty() && !g_Marks[destinationVertex - 1])
   {
      size_t iVertex = q.front();
      q.pop();

      for (size_t jVertex = 0; jVertex < graph[iVertex].size(); jVertex++)
      {
         if (!g_Marks[jVertex] && graph[iVertex][jVertex])
         {
            q.push(jVertex);
            g_Marks[jVertex] = true;
         }
      }
   }
}

int main()
{
   std::ifstream in("input.txt");
   std::ofstream out("output.txt");

   std::ios::sync_with_stdio(false);

   size_t numVertex = 0;
   in >> numVertex;
   std::vector<std::vector<size_t>> graph(numVertex, std::vector<size_t>(numVertex, -1));

   for (size_t i = 0; i < numVertex; i++)
   {
      for (size_t j = 0; j < numVertex; j++)
      {
         size_t weightVertex = 0;
         in >> weightVertex;
         graph[i][j] = weightVertex;
         graph[j][i] = weightVertex;
      }
   }
   
   size_t sourceVertex = 0, destinationVertex = 0;
   in >> sourceVertex >> destinationVertex;

   g_Marks.assign(numVertex, false);
   g_Marks[sourceVertex - 1] = true;

   auto startTime = std::chrono::high_resolution_clock::now();

   doBfs(sourceVertex - 1, destinationVertex - 1, graph);

   auto endTime = std::chrono::high_resolution_clock::now() - startTime;
   auto elapsedTime = std::chrono::duration<double>(endTime).count();

   if (!g_Marks[destinationVertex - 1])
      out << "Route does NOT exist.\n";
   else
      out << "Route exists.\n";

   out << "Algorithm time is " << elapsedTime << " seconds.\n";

   return 0;
}
