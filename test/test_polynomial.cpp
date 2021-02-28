#include "polynomial.h"

#include <gtest.h>


TEST(Monom, can_do_monom_with_correct_coeff) {
	Monom m(1, 100);
	ASSERT_EQ(m.km, 1);
}

TEST(Monom, can_do_monom_with_correct_degree) {
	Monom m(1, 100);
	ASSERT_EQ(m.deg, 100);
}

TEST(Monom, correct_x_degree) {
	Monom m(1, 123);
	ASSERT_EQ(m.dx(), 1);
}

TEST(Monom, correct_y_degree) {
	Monom m(1, 123);
	ASSERT_EQ(m.dy(), 2);
}

TEST(Monom, correct_z_degree) {
	Monom m(1, 123);
	ASSERT_EQ(m.dz(), 3);
}

TEST(Monom, can_add_monons) {
	Monom m1(1, 123);
	Monom m2(2, 123);
	Monom m3(3, 123);
	ASSERT_EQ((m1+m2)==m3, 1);
}

TEST(Monom, cant_add_monoms_with_different_degrees) {
	Monom m1(1, 123);
	Monom m2(2, 124);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(Monom, can__mult_monoms) {
	Monom m1(5, 100);
	Monom m2(6, 123);
	Monom m3(30, 223);
	ASSERT_EQ((m1*m2) == m3, 1);
}

TEST(Monom, cant_mult_monoms_with_too_much_degrees) {
	Monom m1(1, 999), m2(2, 678);
	ASSERT_ANY_THROW(m1 * m2);
}

TEST(Monom, can_compare_monoms_1) {
	Monom m1(5, 100);
	Monom m2(6, 123);
	ASSERT_EQ(m1==m2, 0);
}

TEST(Monom, can_compare_monoms_2) {
	Monom m1(5, 100);
	Monom m2(5, 100);
	ASSERT_EQ(m1 == m2, 1);
}

TEST(Polinom, can_add_polinoms) {
	Polinom p1, p2,p3;
	Monom m1(1, 100), m2(2, 200), m3(3, 300);
	p1.push_back(m1);
	p1.push_back(m2);
	p2.push_back(m3);
	p3.push_back(m1);
	p3.push_back(m2);
	p3.push_back(m3);
	ASSERT_EQ((p1 + p2)==p3, 1);
}

TEST(Polinom, can_add_empty_polinoms) {
	Polinom p1, p2;
	Polinom p3 = p1 + p2;
	ASSERT_EQ((p1 + p2) == p3, 1);
}

TEST(Polinom, can_mult_polinoms) {
	Polinom p1, p2, p3;
	Monom m1(1, 100), m2(2, 200), m3(1, 200), m4(4, 300), m5(1, 300),m6(6,400),m7(8,500);
	p1.push_back(m1);
	p1.push_back(m2);
	p2.push_back(m3);
	p2.push_back(m4);
	p3.push_back(m5);
	p3.push_back(m6);
	p3.push_back(m7);
	ASSERT_EQ((p1 * p2) == p3, 1);
}

TEST(Polinom, can_mult_polinom_with_itself) {
	Polinom p1, p3;
	Monom m1(1, 100), m2(2, 200), m3(1, 200), m4(4, 300), m5(4, 400);
	p1.push_back(m1);
	p1.push_back(m2);
	p3.push_back(m3);
	p3.push_back(m4);
	p3.push_back(m5);
	ASSERT_EQ((p1 * p1) == p3, 1);
}

TEST(Polinom, cant_mult_polinom_with_too_much_degree) {
	Polinom p1;
	Monom m1(1, 900), m2(2, 999);
	p1.push_back(m1);
	p1.push_back(m2);
	Polinom p2(p1);
	ASSERT_ANY_THROW(p1 * p2);
}