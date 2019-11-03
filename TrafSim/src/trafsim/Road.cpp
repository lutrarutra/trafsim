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

bool Road::isHorizontal() const
{
    return abs(m_dir.x) > abs(m_dir.y);
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
    // intersection nodes top left, torright, bot right, bot left.
    std::shared_ptr<Node> &tlNode = intersection_nodes[0];
    std::shared_ptr<Node> &trNode = intersection_nodes[1];
    std::shared_ptr<Node> &brNode = intersection_nodes[2];
    std::shared_ptr<Node> &blNode = intersection_nodes[3];

    if (tlNode == nullptr)
        tlNode = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));

    if (trNode == nullptr)
        trNode = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y - m_lanewidth * 0.5f));

    if (brNode == nullptr)
        brNode = std::make_shared<Node>(sf::Vector2f(pos.x + m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));

    if (blNode == nullptr)
        blNode = std::make_shared<Node>(sf::Vector2f(pos.x - m_lanewidth * 0.5f, pos.y + m_lanewidth * 0.5f));

    //Disconnect old points
    m_brNode->disconnect(m_erNode);
    m_blNode->disconnect(m_elNode);

    //Connect them to new nodes

    if (isHorizontal())
    {
        // ->
        if (m_dir.x > 0)
        {
            m_brNode->connect(blNode);
            m_blNode->connect(trNode);
            //Intersection nodes
            tlNode->connect(m_elNode);
            brNode->connect(m_erNode);
        }
        // <-
        else
        {
            m_brNode->connect(trNode);
            m_blNode->connect(blNode);
            //Intersection nodes
            tlNode->connect(m_erNode);
            brNode->connect(m_elNode);
        }
    }
    else
    {
        // v
        if (m_dir.y > 0)
        {
            m_brNode->connect(tlNode);
            m_blNode->connect(brNode);
            //Intersection nodes
            trNode->connect(m_elNode);
            blNode->connect(m_erNode);
        }
        // ^
        else
        {
            m_brNode->connect(brNode);
            m_blNode->connect(tlNode);
            //Intersection nodes
            trNode->connect(m_erNode);
            blNode->connect(m_elNode);
        }
    }
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
