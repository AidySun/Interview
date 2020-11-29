#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
It's no a Dynamic Planning issue, since the result is not exactly one number, it requires >= target.
Therefore, each time when adding one star, the one with best increament should be chosen. 
Then, we need to sorting or using priority_queue.
*/

const static int FIVE_STARS_MAX = 100;

bool ratingSort(const vector<int>& pr1, const vector<int>& pr2) {
	double d1 = ((pr1[0]+1)*1.0 / (pr1[1]+1)) - (pr1[0]*1.0 / pr1[1]);
	double d2 = ((pr2[0]+1)*1.0 / (pr2[1]+1)) - (pr2[0]*1.0 / pr2[1]);
	return d1 > d2;
}

int fiveSellers(vector<vector<int>> productRatings, int ratingThreshold) {

	double currentRating = 0;
	for (auto pr: productRatings) {
		currentRating += pr[0]*1.0/pr[1] / 3 * 100;
	}

	if (currentRating >= ratingThreshold) return 0;

	int startsNeed = 0;
	while (currentRating < ratingThreshold) {
		std::sort(begin(productRatings), end(productRatings), &ratingSort);
		cout << "current rating: " << currentRating << ", startsNeed: " << startsNeed << ". sorting: ";
		for (auto vv: productRatings) {
			cout << "[" << vv[0] << ", " << vv[1] << "]=" << vv[0]*1.0/vv[1] << " , ";
		}
		cout << endl;
		auto& pr = productRatings[0];

		if (pr[0] == pr[1] || pr[0] >= FIVE_STARS_MAX) continue;

		double rating1 = (pr[0]*1.0 / pr[1]) / 3 * 100;
		double rating2 = ((pr[0]+1)*1.0 / (pr[1]+1)) / 3 * 100;

		currentRating += (rating2 - rating1);
		/*
		currentRating = rating2;
		for (int i = 1; i < productRatings.size(); i++) {
			currentRating += productRatings[i][0]*1.0 / productRatings[i][1];
		}
		*/
		cout << "rating 1: " << rating1 << ", rating2: " << rating2 << ", diff: " << currentRating << endl;
		startsNeed++;

		pr[0] += 1;
		pr[1] += 1;
	}
	return currentRating >= ratingThreshold ? startsNeed : -1;
}

int main() {
	vector<vector<int>> v = {{4, 4}, {1, 2}, {3, 6}};
	int ratingThreshold = 77;
	int ret = fiveSellers(v, ratingThreshold);
	cout << "ret = " << ret << endl;
	return 0;
}

// https://leetcode.com/discuss/interview-question/933383/Amazon-or-OA-2020-or-Five-Star-Sellers
/*
Third-party companies that sell their products on Amazon.com are able to analyze the customer reviews for their products in real time. Imagine that Amazon is creating a category called "five-star sellers" that will only display products sold by companies whose average percentage of five-star reviews per-product is at or above a certain threshold. Given the number of five-star and total reviews for each product a company sells, as well as the threshold percentage, what is the minimum number of additional fivestar reviews the company needs to become a five-star seller?

For example, let's say there are 3 products (n = 3) where productRatings = [[4,4], [1,2], [3, 6]], and the percentage ratings Threshold = 77. The first number for each product in productRatings denotes the number of fivestar reviews, and the second denotes the number of total reviews. Here is how we can get the seller to reach the threshold with the minimum number of additional five-star reviews:

Before we add more five-star reviews, the percentage for this seller is ((4 / 4) + (1/2) + (3/6))/3 = 66.66%
If we add a five-star review to the second product, the percentage rises to ((4 / 4) + (2/3) +(3/6))/3 = 72.22%
If we add another five-star review to the second product, the percentage rises to ((4 / 4) + (3/4) + (3/6))/3 = 75.00%
If we add a five-star review to the third product, the percentage rises to ((4/4) + (3/4) + (4/7))/3 = 77.38%
At this point, the threshold of 77% has been met. Therefore, the answer is 3 because that is the minimum number of additional five-star reviews the company needs to become a five-star seller.

Function Description

Complete the function fiveStarReviews in the editor below.

fiveStarReviews has the following parameters:

int productRatings[n][2]: a 2-dimensional array of integers where the ith element contains two values, the first one denoting fivestar[i] and the second denoting total[i]

int ratingsThreshold: the threshold percentage, which is the average percentage of five-star reviews the products need for the company to be considered a five-star seller

Returns:

int: the minimum number of additional five-star reviews the company needs to meet the threshold ratingsThreshold

Constraints

1<=n<=200
0 <= fivestar<total<=100
1<=ratingsThreshold<100
The array productRatings contains only non-negative integers.
*/