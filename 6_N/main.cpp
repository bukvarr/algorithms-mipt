/*Протокол передачи сообщений позволяет при передаче текста сделать не более K преобразований следующего вида:
 вставка в произвольное место произвольного символа, удаление из произвольного места из произвольного места
 и замена символа на произвольном месте на произвольный.

Известно, что было отправлено слово α, а должно было прийти слово β.
 Найдите слово γ, пришедшее по протоколу, если известно, что длины γ и β совпадают,
 а также число возможных позиций i таких, что γ[i]≠β[i] минимально.

Если же такой γ не существует, то дайте знать. */

#include <iostream>

#include <string>

#include <vector>

void ConstructDP(const std::string& a, const std::string& b,
                         std::vector<std::vector<std::vector<int>>>& dp,
                         int k) {
  for (int i = 1; i <= static_cast<int>(b.length()); ++i) { //dp хранит максималное количество симолов, совпадающих со строкой б среди первых i элементов
    for (int del = 0; del <= k; ++del) { // после del удалерий и add удалений
      for (int add = 0; add <= k; ++add) {
        if (add + del > k) {
          continue;
        }
        if (add > 0) {
          dp[i][del][add] =
                  std::max(dp[i][del][add], dp[i - 1][del][add - 1] + 1);
        }
        if (del > 0) {
          dp[i][del][add] = std::max(dp[i][del][add], dp[i][del - 1][add]);
        }
        if (i - add + del > 0) {
          dp[i][del][add] =
                  std::max(dp[i][del][add],
                           dp[i - 1][del][add] +
                           (i - add + del <= static_cast<int>(a.length()) &&
                            a[i - add + del - 1] == b[i - 1]
                            ? 1
                            : 0));
        }
      }
    }
  }
}

int FindMinDiff(const std::string& a, const std::string& b, int k) {
  std::vector<std::vector<std::vector<int>>> dp(
          b.length() + 1,
          std::vector<std::vector<int>>(k + 1, std::vector<int>(k + 1, 0)));
  ConstructDP(a, b, dp, k);
  int len_a = static_cast<int>(a.length());
  int len_b = static_cast<int>(b.length());
  int min_diff = 0;
  for (int del = 0; del <= k; ++del) {
    int add = len_b - len_a + del;
    if (add >= 0 && k >= del + add) {
      min_diff = std::max(min_diff, dp[len_b][del][add] + k - add - del);
    }
  }
  return min_diff;
}

int main() {
  std::string a;
  std::string b;
  std::cin >> a >> b;
  int k;
  std::cin >> k;
  int len_a = static_cast<int>(a.length());
  int len_b = static_cast<int>(b.length());
  if (k < std::abs(len_a - len_b)) {
    std::cout << -1;
    return 0;
  }
  std::cout << len_b - std::min(FindMinDiff(a, b, k), len_b);
}