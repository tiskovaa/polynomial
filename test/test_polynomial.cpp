
#include "polynomial.h"
#include <gtest.h>

TEST(monom, can_create)
{
    ASSERT_NO_THROW(Monom m(235, 17));
}

TEST(monom, cannt_create_bad_degree)
{
    EXPECT_ANY_THROW(Monom m(2354, 17));
}
TEST(monom, can_return_x_deg)
{
    Monom m(235, 17);
    EXPECT_EQ(m.x_deg(), 2);
}
TEST(monom, can_return_y_deg)
{
    Monom m(235, 17);
    EXPECT_EQ(m.y_deg(), 3);
}
TEST(monom, can_return_z_deg)
{
    Monom m(235, 17);
    EXPECT_EQ(m.z_deg(), 5);
}
TEST(monom, can_return_k)
{
    Monom m(235, 17);
    EXPECT_EQ(m.get_k(), 17);
}
TEST(monom, can_add)
{
    Monom m(235, 17);
    Monom v(235, 13);
    EXPECT_EQ((m + v).get_k(), 30);
}
TEST(monom, cannt_add)
{
    Monom m(235, 17);
    Monom v(25, 13);
    EXPECT_ANY_THROW(m + v);
}
TEST(monom, can_sub)
{
    Monom m(235, 17);
    Monom v(235, 13);
    EXPECT_EQ((m - v).get_k(), 4);
}
TEST(monom, cannt_sub)
{
    Monom m(235, 17);
    Monom v(25, 13);
    EXPECT_ANY_THROW(m - v);
}

TEST(monom, can_mult)
{
    Monom m(235, 17);
    Monom v(147, 13);
    EXPECT_EQ((m * v).get_k(), 221);
    EXPECT_EQ((m * v).degree, 382);
}

TEST(monom, cannt_mult)
{
    Monom m(235, 17);
    Monom v(897, 13);
    EXPECT_ANY_THROW(m * v);
}

TEST(monom, can_mult_on_scal)
{
    Monom m(235, 17);
    EXPECT_EQ((m * 5).get_k(), 85);
}

TEST(Polynom, can_create) {
    Polynom p;
    EXPECT_EQ(p.begin(), p.end());
}

TEST(Polynom, can_create_) {

    ASSERT_NO_THROW(Polynom p);
}

TEST(Polynom, PushBackAndSize) {
    Polynom p;
    Monom m1(123, 2.5);
    Monom m2(456, 3.0);
    p.push_back(m1);
    EXPECT_EQ((*p.begin()).k, 2.5);
    EXPECT_EQ((*p.begin()).degree, 123);
    p.push_back(m2);
    mlist<Monom>::iterator it = p.begin();
    ++it;
    EXPECT_EQ((*it).k, 3.0);
    EXPECT_EQ((*it).degree, 456);
}

TEST(PolynomialTest, MonomEquality) {
    Monom m1(123, 2.5);
    Monom m2(123, 2.5);
    Monom m3(456, 3.0);
    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);
}

TEST(PolynomialTest, can_Add)
{
    Polynom p1;
    p1.push_back(Monom(123, 25));
    p1.push_back(Monom(456, 3));
    Polynom p2;
    p2.push_back(Monom(123, 15));
    ASSERT_NO_THROW(p1 + p2);

}
TEST(PolynomialTest, can_mult)
{
    Polynom p1;
    p1.push_back(Monom(123, 25));
    p1.push_back(Monom(456, 3));
    Polynom p2;
    p2.push_back(Monom(123, 15));
    ASSERT_NO_THROW(p1 * p2);

}
TEST(PolynomialTest, Addition) {
    Polynom p1;
    p1.push_back(Monom(123, 25));
    p1.push_back(Monom(456, 3));
    Polynom p2;
    p2.push_back(Monom(123, 15));
    Polynom p3 = p1 + p2;
    mlist<Monom>::iterator it = p3.begin();
    EXPECT_EQ((*it).k, 40);
    EXPECT_EQ((*it).degree, 123);
    it++;
    EXPECT_EQ((*it).k, 3);
    EXPECT_EQ((*it).degree, 456);
}
TEST(PolynomialTest, Multiplication) {
    Polynom p1;
    p1.push_back(Monom(123, 2.0));
    Polynom p2;
    p2.push_back(Monom(456, 3.0));
    Polynom p3 = p1 * p2;
    mlist<Monom>::iterator it = p3.begin();
    EXPECT_EQ((*it).k, 6.0);
    EXPECT_EQ((*it).degree, 579);
}
TEST(PolynomialTest, ScalarMultiplication) {
    Polynom p1;
    p1.push_back(Monom(123, 2.0));
    p1.push_back(Monom(456, 3.0));
    Polynom p2 = p1 * 2.0;
    mlist<Monom>::iterator it = p2.begin();
    EXPECT_EQ((*it).k, 4.0);
    EXPECT_EQ((*it).degree, 123);
    ++it;
    EXPECT_EQ((*it).k, 6.0);
    EXPECT_EQ((*it).degree, 456);
}