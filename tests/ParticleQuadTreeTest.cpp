#include <gtest/gtest.h>

#include "Slinky/Particle/Particle.hpp"
#include "Slinky/Containers/ParticleQuadTree.hpp"

TEST (ParticleTreeTest, TwoParticles)
{
    using namespace Slinky::Containers;
    using namespace Slinky::Particle;

    ParticleCfg cfg {
        {5, 5},
        0,
        0,
        0,
        0,
        0
    };

    Particle p1 {cfg};
    cfg.pos = {10, 10};
    Particle p2 {cfg};

    ParticleQuadTree tree {
        {{0, 0}, {20, 20}},
        0
    };

    tree.Insert(&p1);
    tree.Insert(&p2);

    std::vector<std::pair<Particle*, Particle*>> pairs;

    tree.GetPairs(pairs);

    EXPECT_EQ(1, pairs.size());
    EXPECT_EQ(&p1, pairs[0].first);
    EXPECT_EQ(&p2, pairs[0].second);
}

TEST (ParticleTreeTest, ThreeParticles)
{
    using namespace Slinky::Containers;
    using namespace Slinky::Particle;

    ParticleCfg cfg {
        {0, 0},
        0,
        0,
        0,
        0,
        0
    };

    cfg.pos = {2, 2};
    Particle p1 {cfg};

    cfg.pos = {4, 4};
    Particle p2 {cfg};

    cfg.pos = {6, 6};
    Particle p3 {cfg};

    ParticleQuadTree tree {
        {{0, 0}, {20, 20}},
        0
    };

    tree.Insert(&p1);
    tree.Insert(&p2);
    tree.Insert(&p3);

    std::vector<std::pair<Particle*, Particle*>> pairs;
    tree.GetPairs(pairs);

    EXPECT_EQ(3, pairs.size());

    auto oneTwo { std::find(pairs.begin(), pairs.end(), std::make_pair(&p1, &p2)) };
    auto oneThree { std::find(pairs.begin(), pairs.end(), std::make_pair(&p1, &p3)) };
    auto twoThree { std::find(pairs.begin(), pairs.end(), std::make_pair(&p2, &p3)) };

    EXPECT_NE(pairs.end(), oneTwo);
    EXPECT_NE(pairs.end(), oneThree);
    EXPECT_NE(pairs.end(), twoThree);
}

TEST (ParticleTreeTest, FiveParticles)
{
    using namespace Slinky::Containers;
    using namespace Slinky::Particle;

    ParticleCfg cfg {
            {5, 5},
            0,
            0,
            0,
            0,
            0
    };

    Particle p1 {cfg};

    cfg.pos = {7, 7};
    Particle p2 {cfg};

    cfg.pos = {5, 15};
    Particle p3 {cfg};

    cfg.pos = {15, 5};
    Particle p4 {cfg};

    cfg.pos = {15, 15};
    Particle p5 {cfg};

    ParticleQuadTree tree {
            {{0, 0}, {20, 20}},
            0
    };

    tree.Insert(&p1);
    tree.Insert(&p2);
    tree.Insert(&p3);
    tree.Insert(&p4);
    tree.Insert(&p5);

    std::vector<std::pair<Particle*, Particle*>> pairs;

    tree.GetPairs(pairs);

    EXPECT_EQ(1, pairs.size());
    EXPECT_EQ(&p1, pairs[0].first);
    EXPECT_EQ(&p2, pairs[0].second);
}

TEST (ParticleTreeTest, EightParticles)
{
    using namespace Slinky::Containers;
    using namespace Slinky::Particle;

    ParticleCfg cfg {
            {0, 0},
            0,
            0,
            0,
            0,
            0,
    };

    cfg.pos = {5, 5};
    Particle p1 {cfg};
    cfg.pos = {7, 5};
    Particle p2 {cfg};

    cfg.pos = {5, 15};
    Particle p3 {cfg};
    cfg.pos = {7, 15};
    Particle p4 {cfg};

    cfg.pos = {15, 5};
    Particle p5 {cfg};
    cfg.pos = {17, 5};
    Particle p6 {cfg};

    cfg.pos = {15, 15};
    Particle p7 {cfg};
    cfg.pos = {17, 15};
    Particle p8 {cfg};

    ParticleQuadTree tree {
            {{0, 0}, {20, 20}},
            0
    };

    tree.Insert(&p1);
    tree.Insert(&p2);
    tree.Insert(&p3);
    tree.Insert(&p4);
    tree.Insert(&p5);
    tree.Insert(&p6);
    tree.Insert(&p7);
    tree.Insert(&p8);

    std::vector<std::pair<Particle*, Particle*>> pairs;
    tree.GetPairs(pairs);

    EXPECT_EQ(4, pairs.size());

    auto firstPair = std::find(pairs.begin(), pairs.end(), std::make_pair(&p1, &p2));
    EXPECT_EQ(true, firstPair != pairs.end());

    auto secondPair = std::find(pairs.begin(), pairs.end(), std::make_pair(&p3, &p4));
    EXPECT_EQ(true, secondPair != pairs.end());

    auto thirdPair = std::find(pairs.begin(), pairs.end(), std::make_pair(&p5, &p6));
    EXPECT_EQ(true, thirdPair != pairs.end());

    auto fourthPair = std::find(pairs.begin(), pairs.end(), std::make_pair(&p7, &p8));
    EXPECT_EQ(true, fourthPair != pairs.end());
}