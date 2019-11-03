#include "trafsim/Road.hpp"

namespace TrafSim
{

Road::Road(const Road &prev_road, const std::shared_ptr<Node> &end)
    : m_brNode(prev_road.m_brNode), m_blNode(prev_road.m_blNode), m_begin(prev_road.m_end), m_end(end), m_dir(VectorMath::Normalize(m_end->getPos() - m_begin->getPos())), m_lanewidth(prev_road.m_lanewidth)
{
    //Permendicular direction to m_dir
    sf::Vector2f pdir = {-m_dir.y, m_dir.x};

    m_brNode = std::make_shared<Node>(m_begin->getPos() + pdir * m_lanewidth * 0.5f, sf::Color::Blue);
    m_blNode = std::make_shared<Node>(m_end->getPos() - pdir * m_lanewidth * 0.5f, sf::Color::Blue);
    init();
}

Road::Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width)
    : m_begin(begin), m_end(end), m_dir(VectorMath::Normalize(m_end->getPos() - m_begin->getPos())), m_lanewidth(lane_width)
{
    //Permendicular direction to m_dir
    sf::Vector2f pdir = {-m_dir.y, m_dir.x};

    m_brNode = std::make_shared<Node>(m_begin->getPos() + pdir * m_lanewidth * 0.5f, sf::Color::Blue);
    m_blNode = std::make_shared<Node>(m_end->getPos() - pdir * m_lanewidth * 0.5f, sf::Color::Blue);

    init();
}

void Road::init()
{

    m_erNode = std::make_shared<Node>(m_brNode->getPos() + (m_end->getPos() - m_begin->getPos()));
    m_elNode = std::make_shared<Node>(m_blNode->getPos() - (m_end->getPos() - m_begin->getPos()));

    //Permendicular direction to m_dir
    sf::Vector2f pdir = {-m_dir.y, m_dir.x};

    m_vertices.emplace_back(m_begin->getPos() + pdir * m_lanewidth);

    m_vertices.emplace_back(m_begin->getPos() - pdir * m_lanewidth);

    m_vertices.emplace_back(m_end->getPos() + pdir * m_lanewidth);

    m_vertices.emplace_back(m_end->getPos() - pdir * m_lanewidth);

    m_brNode->connect(m_erNode);
    m_blNode->connect(m_elNode);
}

void Road::createIntersection(std::shared_ptr<Road> another, sf::Vector2f pos, std::shared_ptr<Node> *intersection_nodes)
{
    std::shared_ptr<Node> &brNode1 = intersection_nodes[0];
    std::shared_ptr<Node> &brNode2 = intersection_nodes[1];
    std::shared_ptr<Node> &blNode1 = intersection_nodes[2];
    std::shared_ptr<Node> &blNode2 = intersection_nodes[3];

    m_brNode->disconnect(m_erNode);

    if (brNode1 == nullptr || brNode2 == nullptr)
    {
        if (m_dir.x > m_dir.y)
        {
            brNode1 = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));
            brNode2 = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));
        }
        else
        {
            brNode1 = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));
            brNode2 = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));
        }
    }

    brNode1->connect(brNode2);
    brNode1->connect(another->m_elNode);
    brNode2->connect(m_erNode);
    brNode2->connect(another->m_erNode);

    m_blNode->disconnect(m_elNode);

    if (blNode1 == nullptr || blNode2 == nullptr)
    {
        if (m_dir.x > m_dir.y)
        {
            blNode1 = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));
            blNode2 = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));
        }
        else
        {
            blNode1 = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));
            blNode2 = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));
        }
    }

    blNode1->connect(blNode2);
    blNode1->connect(another->m_erNode);
    blNode2->connect(m_elNode);
    blNode2->connect(another->m_elNode);
}

void Road::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&m_vertices[0], m_vertices.size(), sf::TriangleStrip);
    target.draw(*m_brNode);
    target.draw(*m_blNode);
    target.draw(*m_erNode);
    target.draw(*m_elNode);
}

} // namespace TrafSim
