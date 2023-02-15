#include "pch.h"
#include <list>
#include <stdlib.h>
#include <iostream>
#include "include/List.hpp"
#include "include/Saat.hpp"
#include "include/Node.hpp"
#include "include/HepsiHarranda.hpp"
#include "gmock/gmock.h"
#include "include/AVL.hpp"
#include "include/Gorusme.hpp"
#include "include/Util.hpp"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AnyNumber;
using namespace std;

/*
// PAREMETERIZED CLASSES FOR PAREMETERIZED TEST CASES
*/
class ParameterizedFrontTest : public 
		::testing::TestWithParam<int> {};

class ParameterizedDequeueTest : public		
		::testing::TestWithParam<int> {};

class ParameterizedGreaterTest : public 
		::testing::TestWithParam<std::tuple<int, int>> {};

class ParameterizedLessTest : public 
		::testing::TestWithParam<std::tuple<int, int>> {};

class ParameterizedMinTest : public 
		::testing::TestWithParam<std::tuple<int, int, int>> {};

class ParameterizedLinkedList : public ::testing::TestWithParam<int> {
public:
	List<int>* list = new List<int>();
	Node<int>* asd = list->dummyHead;
	void SetUp() {
	}
	void TearDown() {
		list->clear();
	}
};

class ParameterizedSwapTest : public ::testing::TestWithParam<std::pair<int, int>> {
protected:
	void SetUp() override {
		a = GetParam().first;
		b = GetParam().second;
	}
	int a;
	int b;
};

class ParameterizedHepsiHarrandaTest : public testing::TestWithParam<std::tuple<int, Temsilci, Temsilci>> {
protected:
	HepsiHarranda hh;
	List<Temsilci> temsilciler;
	

	void SetUp() {
		Temsilci temsilci1(1, "John");
		Temsilci temsilci2(2, "Jane");
		Temsilci temsilci3(3, "Bob");

		hh.temsilciEkle(temsilci1);
		hh.temsilciEkle(temsilci2);
		hh.temsilciEkle(temsilci3);
	}
	void TearDown() {

	}
};

/*
// MOCK CLASSES
*/
class MockMusteri : public Musteri {
public:
	// Define mock methods for the methods we want to test.
	MOCK_CONST_METHOD0(uyelikDurumu, bool());
	MOCK_CONST_METHOD0(cuzdanDurumu, bool());
	MOCK_CONST_METHOD0(aylikHarcama, int());
	MOCK_CONST_METHOD0(yorumSayisi, int());
	MOCK_CONST_METHOD0(urunCesidi, int());
};

class MockHepsiHarranda : public HepsiHarranda {
public:

	MOCK_METHOD(void, temsilciEkle, (Temsilci));
	MOCK_METHOD(void,musterileriDosyadanOku,());
	MOCK_METHOD( Temsilci, getTemsilci, (int) );
	MOCK_METHOD(Temsilci, siradakiTemsilciGetir, ());
};

class MockTemsilci : public Temsilci {
public:

	MOCK_METHOD(void, Temsilci, (int,string ));
};

template<class T>
class MockList : List<T>{
public:
	MOCK_METHOD(int, getSize, (), (const));
	MOCK_METHOD(bool, isEmpty, (), (const));
	MOCK_METHOD(Node<T>*, begin, (), (const));
	MOCK_METHOD(void, insert, (Node<T>*, const T&), ());
	MOCK_METHOD(Node<T>*, erase, (Node<T>*), ());
	MOCK_METHOD(void, clear, (), ());
	MOCK_METHOD(void, push_front, (const T&), ());
	MOCK_METHOD(void, push_back, (const T&), ());
	MOCK_METHOD(void, pop_front, (), ());
	MOCK_METHOD(void, pop_back, (), ());
};

template<class T, class Compare>
class MockAVL : public AVL<T, Compare> {
public:
	MOCK_METHOD(AVLNode<T>*, ll_rotate, (AVLNode<T>*), ());
	MOCK_METHOD(AVLNode<T>*, rr_rotate, (AVLNode<T>*), ());
	MOCK_METHOD(AVLNode<T>*, lr_rotate, (AVLNode<T>*), ());
	MOCK_METHOD(AVLNode<T>*, rl_rotate, (AVLNode<T>*), ());
	MOCK_METHOD(int, different, (AVLNode<T>*), ());
	MOCK_METHOD(AVLNode<T>*, balance, (AVLNode<T>*), ());
	MOCK_METHOD(AVLNode<T>*, insert, (AVLNode<T>*, const T&), ());
	MOCK_METHOD(AVLNode<T>*, find, (AVLNode<T>*, const T&), ());
	MOCK_METHOD(int, height, (AVLNode<T>*), ());
	MOCK_METHOD(void, inorder, (AVLNode<T>*), ());
};

/*
// MOCK TEST CASES
*/
TEST(AVLTest, MockTestLlRotate) {
	MockAVL<int, int> avl;

	AVLNode<int> node1(1);
	AVLNode<int> node2(2);

	EXPECT_CALL(avl, ll_rotate(&node1))
		.WillOnce(::testing::Return(&node2));
	AVLNode<int>* result = avl.ll_rotate(&node1);

	EXPECT_EQ(result, &node2);
};
TEST(MockListTest, TestIsEmpty) {
	MockList<int> list;

	EXPECT_CALL(list, isEmpty())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));

	EXPECT_TRUE(list.isEmpty());
	EXPECT_FALSE(list.isEmpty());
};
TEST(AVLTest, MockTestInsert) {
	MockAVL<int,int> avl;

	AVLNode<int> node1(1);
	AVLNode<int> node2(2);

	EXPECT_CALL(avl, insert(nullptr, 1))
		.WillOnce(::testing::Return(&node1));
	EXPECT_CALL(avl, insert(&node1, 2))
		.WillOnce(::testing::Return(&node2));


	AVLNode<int>* result1 = avl.insert(nullptr, 1);
	AVLNode<int>* result2 = avl.insert(&node1, 2);

	EXPECT_EQ(result1, &node1);
	EXPECT_EQ(result2, &node2);
};
TEST(AVLTest, MockTestFind) {
	MockAVL<int, int> avl;

	AVLNode<int> node1(1);
	AVLNode<int> node2(2);

	EXPECT_CALL(avl, find(nullptr, 1))
		.WillOnce(::testing::Return(&node1));
	EXPECT_CALL(avl, find(&node1, 2))
		.WillOnce(::testing::Return(&node2));

	AVLNode<int>* result1 = avl.find(nullptr, 1);
	AVLNode<int>* result2 = avl.find(&node1, 2);

	EXPECT_EQ(result1, &node1);
	EXPECT_EQ(result2, &node2);
}
TEST(MockTemsilci, MocksiradakiTemsi) {
	MockTemsilci temsilci;
	temsilci.temsilciAdi = "ali";
	temsilci.temsilciID = 5;
	HepsiHarranda* harr = new HepsiHarranda;;
	harr->temsilciEkle(temsilci);
	Temsilci tm = harr->siradakiTemsilciGetir();
	ASSERT_EQ(tm.temsilciAdi, temsilci.temsilciAdi);
	ASSERT_EQ(tm.temsilciID, temsilci.temsilciID);
	delete harr;
};


/*
// PAREMETERIZED TEST CASES
*/
TEST_P(ParameterizedDequeueTest, Test) {
	Queue<int> q;

	int data = GetParam();
	q.enqueue(1);
	q.enqueue(data);

	q.dequeue();

	ASSERT_EQ(q.front(), data);
};
INSTANTIATE_TEST_CASE_P(InstantiationName, ParameterizedDequeueTest, ::testing::Range(0, 25));

TEST_P(ParameterizedFrontTest, TestFrontQueue) {
	
	int data = GetParam();
	Queue<int> q;

	q.enqueue(data);

	ASSERT_EQ(q.front(), data);
};
INSTANTIATE_TEST_CASE_P(TestFrontQueue, ParameterizedFrontTest, ::testing::Values(1, 2, 3));

TEST_P(ParameterizedGreaterTest, TestGreaterOperator) {

	const int lhs = std::get<0>(GetParam());
	const int rhs = std::get<1>(GetParam());

	Greater<int> greater;

	EXPECT_TRUE(greater(lhs, rhs));
};
INSTANTIATE_TEST_CASE_P(GreaterTest, ParameterizedGreaterTest, ::testing::Values(
				std::make_tuple(5, 1), std::make_tuple(1, 0),
				std::make_tuple(-1, -11), std::make_tuple(235, 1)));

TEST_P(ParameterizedLessTest, TestGreaterOperator) {

	const int lhs = std::get<0>(GetParam());
	const int rhs = std::get<1>(GetParam());

	Less<int> less;

	EXPECT_FALSE(less(lhs, rhs));
};
INSTANTIATE_TEST_CASE_P(GreaterTest, ParameterizedLessTest, ::testing::Values(
	std::make_tuple(5, 1), std::make_tuple(1, 0),
	std::make_tuple(-1, -11), std::make_tuple(235, 1)));

TEST_P(ParameterizedMinTest, ReturnsMinimum) {
	int x = std::get<0>(GetParam());
	int y = std::get<1>(GetParam());
	int expected = std::get<2>(GetParam());
	int calculated = min_t(x, y);
	EXPECT_EQ(calculated, expected);
}
INSTANTIATE_TEST_SUITE_P(ReturnsMinimum, ParameterizedMinTest,::testing::Values(
			std::make_tuple(0, 1, 0),std::make_tuple(1, 0, 0),
			std::make_tuple(-1, 1, -1),	std::make_tuple(1, 1, 1)));


TEST_P(ParameterizedSwapTest, TestSwapT) {
	swap_t(a, b);
	EXPECT_EQ(a, GetParam().second);
	EXPECT_EQ(b, GetParam().first);
}
INSTANTIATE_TEST_CASE_P(SwapTest, ParameterizedSwapTest, ::testing::Values(
				std::make_pair(5, 10), std::make_pair(100, 50),
				std::make_pair(-5, 10), std::make_pair(1000000, 50000000)));

TEST_P(ParameterizedHepsiHarrandaTest, GetTemsilciTest) {
	int id = std::get<0>(GetParam());
	Temsilci expected = std::get<1>(GetParam());
	Temsilci default_value = std::get<2>(GetParam());

	EXPECT_EQ(hh.getTemsilci(id).temsilciID, expected.temsilciID);


	EXPECT_EQ(hh.getTemsilci(-1).temsilciAdi, default_value.temsilciAdi);
}
INSTANTIATE_TEST_SUITE_P(GetTemsilciTest, ParameterizedHepsiHarrandaTest, testing::Values(
	std::make_tuple(1, Temsilci(1, "John"), Temsilci(-1, "")),
	std::make_tuple(2, Temsilci(2, "Jane"), Temsilci(-1, "")),
	std::make_tuple(3, Temsilci(3, "Bob"), Temsilci(-1, ""))));

TEST_P(ParameterizedLinkedList, PushBackTestP) {

	int data1 = GetParam();
	list->push_back(data1);
	ASSERT_EQ(data1, asd->next->data);
}
INSTANTIATE_TEST_CASE_P(PushBackTestP, ParameterizedLinkedList, ::testing::Range(-10, 10));

TEST_P(ParameterizedLinkedList, PushTest) {
	int param = GetParam();
	list->push_front(param);
	int data1 = asd->next->data;
	ASSERT_EQ(data1, param);
} 
INSTANTIATE_TEST_CASE_P(PushTest, ParameterizedLinkedList, ::testing::Values(NULL, 5, 20, 40, 80, 12, 50, -50));

TEST_P(ParameterizedLinkedList, GetSizeTest) {
	list->push_front(18);
	list->push_front(19);
	int size = list->getSize();
	ASSERT_EQ(size, 2);
}
INSTANTIATE_TEST_CASE_P(GetSizeTest, ParameterizedLinkedList, ::testing::Range(0, 1000));

/*
// NORMALY UNIT TEST CASES
*/
TEST(MusteriTest, OncelikPuaniHesaplaTest) {
	MockMusteri m;

	EXPECT_CALL(m, uyelikDurumu()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(m, cuzdanDurumu()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(m, aylikHarcama()).WillRepeatedly(::testing::Return(4000));
	EXPECT_CALL(m, yorumSayisi()).WillRepeatedly(::testing::Return(8));
	EXPECT_CALL(m, urunCesidi()).WillRepeatedly(::testing::Return(10));
	int oncelik = m.Musteri::oncelikPuaniHesapla();
	
	ASSERT_EQ(oncelik, 25);
}
TEST(LinkedList, PushFrontTest) {

	List<int>* list = new List<int>();
	Node<int>* asd = list->dummyHead;
	list->push_front(18);
	list->push_front(19);
	int data1 = asd->next->data;
	int data2 = asd->next->next->data;
	ASSERT_EQ(data1, 19);
	ASSERT_EQ(data2, 18);
	list->clear();
	delete list;
}
TEST(LinkedList, PushBackTest) {
	List<int>* list = new List<int>();
	Node<int>* asd = list->dummyHead;
	list->push_front(18);
	list->push_back(19);
	int data1 = asd->next->data;
	ASSERT_EQ(data1, 18);
	int data2 = asd->next->next->data;
	ASSERT_EQ(data2, 19);
	list->clear();
	delete list;
}
TEST(LinkedList, ClearTest) {
	List<int>* list = new List<int>();
	Node<int>* asd = list->dummyHead;
	list->push_back(18);
	list->push_front(19);
	list->clear();
	int size = list->getSize();
	ASSERT_EQ(size, 0);
	delete list;
};


/*
// REPEATED TEST CASES
*/
TEST(LinkedList, IsEmptyTest) {
	List<int>* list = new List<int>();
	ASSERT_EQ(list->isEmpty(), 1);
}
TEST(AVLTest, RR_Rotate) {
	AVL<int, std::less<int>> avl;

	AVLNode<int>* root = new AVLNode<int>(10);
	root->left = new AVLNode<int>(5);
	root->right = new AVLNode<int>(20);
	root->right->left = new AVLNode<int>(15);
	root->right->right = new AVLNode<int>(30);

	AVLNode<int>* new_root = avl.rr_rotate(root);
	EXPECT_EQ(new_root->data, 20);
	EXPECT_EQ(new_root->left->data, 10);
	EXPECT_EQ(new_root->right->data, 30);
	EXPECT_EQ(new_root->left->left->data, 5);
	EXPECT_EQ(new_root->left->right->data, 15);
}
TEST(AVLTest, LR_Rotate) {
	AVL<int, std::less<int>> avl;

	AVLNode<int>* root = new AVLNode<int>(30);
	root->left = new AVLNode<int>(10);
	root->right = new AVLNode<int>(40);
	root->left->left = new AVLNode<int>(5);
	root->left->right = new AVLNode<int>(20);

	AVLNode<int>* new_root = avl.lr_rotate(root);
	EXPECT_EQ(new_root->data, 20);
	EXPECT_EQ(new_root->left->data, 10);
	EXPECT_EQ(new_root->right->data, 30);
	EXPECT_EQ(new_root->left->left->data, 5);
	EXPECT_EQ(new_root->right->right->data, 40);
}
TEST(AVLTest, RL_Rotate) {
	AVL<int, std::less<int>> avl;

	AVLNode<int>* root = new AVLNode<int>(10);
	root->left = new AVLNode<int>(5);
	root->right = new AVLNode<int>(20);
	root->right->left = new AVLNode<int>(15);
	root->right->right = new AVLNode<int>(30);

	AVLNode<int>* new_root = avl.rl_rotate(root);
	EXPECT_EQ(new_root->data, 15);
	EXPECT_EQ(new_root->left->data, 10);
	EXPECT_EQ(new_root->right->data, 20);
	EXPECT_EQ(new_root->left->left->data, 5);
	EXPECT_EQ(new_root->right->right->data, 30);
}
TEST(AVLTest, HeightTest) {


	AVL<int> avl;

	// Check the height of an empty tree
	EXPECT_EQ(avl.height(avl.root), 0);

	// Insert some elements into the tree
	avl.insert(10);
	avl.insert(5);
	avl.insert(15);

	// Check the height of the tree
	EXPECT_EQ(avl.height(avl.root), 2);

	// Insert some more elements into the tree
	avl.insert(3);
	avl.insert(7);
	avl.insert(12);
	avl.insert(20);

	// Check the height of the tree again
	EXPECT_EQ(avl.height(avl.root), 3);
}

///MAIN FUNC.
int main(int argc, char** argv) {


	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();										///BEFORE RUN ALL TEST CASES
	
	
	testing::GTEST_FLAG(filter) = "AVLTest.HeightTest";     /////////////////////
	testing::GTEST_FLAG(repeat) = 100;						//
	RUN_ALL_TESTS();										//
	testing::GTEST_FLAG(filter) = "AVLTest.RR_Rotate";		//
	testing::GTEST_FLAG(repeat) = 15;						//  REPEATED
	RUN_ALL_TESTS();										//  TESTS
	testing::GTEST_FLAG(filter) = "AVLTest.LR_Rotate";		//  FILTERS
	testing::GTEST_FLAG(repeat) = 14;						//	AND COUNT 
	RUN_ALL_TESTS();										//	SETTINGS
	testing::GTEST_FLAG(filter) = "AVLTest.RL_Rotate";		//
	testing::GTEST_FLAG(repeat) = 16;						//
	RUN_ALL_TESTS();										//
	testing::GTEST_FLAG(filter) = "LinkedList.IsEmptyTest"; //
	testing::GTEST_FLAG(repeat) = 10;						///////////////////////
	return RUN_ALL_TESTS();
}