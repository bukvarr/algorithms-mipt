/*Тут нет легенды, чистая классика.

Вам требуется написать программу, которая по заданной последовательности находит максимальную невозрастающую её подпоследовательность
 (то есть такую последовательность чисел ai1,ai2,…,aik (i1<i2<…<ik), что ai1≥ai2≥…≥aik
 и не существует последовательности с теми же свойствами длиной k+1). */

#include <iostream>

#include <vector>

void ConstructingDP(const std::vector<long long>& nums, std::vector<int>& dp,
                    std::vector<size_t>& max_pos) {
  dp[0] = 0;
  max_pos[0] = 0; //комментарий в функции FindingSequence
  size_t n = nums.size();
  for (size_t i = 1; i < n; ++i) {
    size_t l = 0;
    size_t r = n;
    while (r - l > 1) { // bin search of new pos
      size_t m = (l + r) / 2;
      if (dp[m] == -1 || nums[dp[m]] < nums[i]) {
        r = m;
      } else {
        l = m;
      }
    }
    if (nums[dp[l]] >= nums[i]) { //updating pos
      dp[l + 1] = i;
      max_pos[i] = l + 1;
    } else {
      if (l + 1 == n || dp[l + 1] == -1) {
      }
      dp[l] = i;
      max_pos[i] = l;
    }
  }
}

std::vector<int> GatheringIndexes(const std::vector<int>& dp,
                                  const std::vector<size_t>& max_pos) {
  size_t n = dp.size();
  size_t length = 0;
  for (size_t i = n - 1; i > 0; --i) {
    if (dp[i] != -1) {
      length = i;
      break;
    }
  }
  int index = dp[length];
  std::vector<int> vect;
  while (true) {
    if (max_pos[index] == length) {
      vect.push_back(index + 1);
      --length;
    }
    --index;
    if (length == static_cast<size_t>(-1)) {
      break;
    }
  }
  return vect;
}

void FindingSequence(size_t n, std::vector<long long> nums, std::vector<int>& indexes) {
  std::vector<int> dp(n, -1); //on each iteration max sequence on first i elements with length = 1, ... , n
  std::vector<size_t> max_pos(n, -1); //max position of element 0 <= i < n
  ConstructingDP(nums, dp, max_pos);
  indexes = GatheringIndexes(dp, max_pos);
}



int main() {
  size_t n;
  std::cin >> n;
  std::vector<long long> nums(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  std::vector<int> indexes;
  FindingSequence(n, nums, indexes);
  std::cout << indexes.size() << '\n';
  for (int i = indexes.size() - 1; i >= 0; --i) {
    std::cout << indexes[i] << " ";
  }
}