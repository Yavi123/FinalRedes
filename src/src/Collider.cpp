#include "src/include/Collider.h"
#include "src/include/GameObject.h"
#include "src/include/RenderCube.h"
#include "src/include/Transform.h"
#include "src/include/Vector2.h"
#include "src/include/CollissionManager.h"
#include "src/include/SDL_Utils.h"

Collider::Collider() : collider({0,0,1,1}), isTrigger(false), colliding(false) {};

Collider::~Collider(){
    CollissionManager::getInstance()->deregisterObject(gameObject);
};

void Collider::initComponent(const SDL_Rect& coll){
    collider.w =coll.w;
    collider.h = coll.h;
    collider.x = coll.x;
    collider.y = coll.y;
}

void Collider::update(float dt){
    Transform* tr = gameObject->getTransform();
	collider.x = tr->getPosition().x;
	collider.y = tr->getPosition().y;
	collider.w = tr->getSize().x;
	collider.h = tr->getSize().y;

	//SDL_Utils::Instance()->DrawRect(collider, { 0,0,255,255 });
}

void Collider::onCollission(GameObject* other){
	if (isTrigger || other->getComponent<Collider>()->IsTrigger()) return;
	if(gameObject->getTransform()->getVelocity().x == 0 && gameObject->getTransform()->getVelocity().y == 0) return;

	auto transform = gameObject->getTransform();

	SDL_Rect otherCol = other->getComponent<Collider>()->collider;

	SDL_Rect result;

	if (SDL_IntersectRect(&collider, &otherCol, &result)) {
		
		if (result.w > result.h) {
			if (collider.y > otherCol.y && transform->getVelocity().y < 0) {
				transform->setPosition({transform->getPosition().x, transform->getPosition().y + (result.h + 1)});
			}
			else if (collider.y <= otherCol.y && transform->getVelocity().y > 0) {
				transform->setPosition({transform->getPosition().x, transform->getPosition().y - result.h});
			}
			transform->setVelocity({ transform->getVelocity().x,0 });
		} else {
			if (collider.x > otherCol.x && transform->getVelocity().x < 0) {
				transform->setPosition({transform->getPosition().x + (result.w + 1), transform->getPosition().y});
			}
			else if (collider.x <= otherCol.x && transform->getVelocity().x > 0) {
				transform->setPosition({transform->getPosition().x - (result.w + 1), transform->getPosition().y});
			}
			transform->setVelocity({ 0,transform->getVelocity().y });
		}
	}
}

void Collider::start(){
    CollissionManager::getInstance()->registerObject(gameObject);
    Transform* tr = gameObject->getTransform();
    collider.h = tr->getSize().y;
    collider.w = tr->getSize().x;
    collider.x = tr->getPosition().x;
    collider.y = tr->getPosition().y;
}

void Collider::SetAsTrigger() {
	isTrigger = !isTrigger;
}
bool Collider::IsTrigger() {
	return isTrigger;
}

bool Collider::isColliding(GameObject* other){
    Transform* tr = gameObject->getTransform();
    Transform* otherTr = other->getTransform();
    SDL_Rect otherCol= other->getComponent<Collider>()->collider;

    return collidesWithRotation(tr->getPosition(), (float)collider.w, (float)collider.h, tr->getRotation(),
                                otherTr->getPosition(), (float)otherCol.w, (float)otherCol.h, otherTr->getRotation());
}


bool Collider::collidesWithRotation(const Vector2 &o1Pos, float o1Width,
		float o1Height, float o1Rot, const Vector2 &o2Pos, float o2Width,
		float o2Height, float o2Rot) {
	Vector2 Ac = o1Pos + Vector2(o1Width / 2.0f, o1Height / 2.0f);

	float angleA = o1Rot;

	Vector2 Alu = Ac
			+ Vector2(-o1Width / 2.0f, -o1Height / 2.0f).rotate(angleA);
	Vector2 Aru = Ac
			+ Vector2(o1Width / 2.0f, -o1Height / 2.0f).rotate(angleA);
	Vector2 All = Ac
			+ Vector2(-o1Width / 2.0f, o1Height / 2.0f).rotate(angleA);
	Vector2 Arl = Ac
			+ Vector2(o1Width / 2.0f, o1Height / 2.0f).rotate(angleA);

	float angleB = o2Rot;

	Vector2 Bc = o2Pos + Vector2(o2Width / 2.0f, o2Height / 2.0f);

	Vector2 Blu = Bc
			+ Vector2(-o2Width / 2.0f, -o2Height / 2.0f).rotate(angleB);
	Vector2 Bru = Bc
			+ Vector2(o2Width / 2.0f, -o2Height / 2.0f).rotate(angleB);
	Vector2 Bll = Bc
			+ Vector2(-o2Width / 2.0f, o2Height / 2.0f).rotate(angleB);
	Vector2 Brl = Bc
			+ Vector2(o2Width / 2.0f, o2Height / 2.0f).rotate(angleB);

	return PointInRectangle(Alu, Aru, All, Arl, Blu)
			|| PointInRectangle(Alu, Aru, All, Arl, Bru)
			|| PointInRectangle(Alu, Aru, All, Arl, Bll)
			|| PointInRectangle(Alu, Aru, All, Arl, Brl)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Alu)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Aru)
			|| PointInRectangle(Blu, Bru, Bll, Brl, All)
			|| PointInRectangle(Blu, Bru, Bll, Brl, Arl);
}

bool Collider::PointInRectangle(const Vector2 &A, const Vector2 &C,
		const Vector2 &B, const Vector2 &D, const Vector2 &P) {
	if (PointInTriangle(A, B, C, P))
		return true;
	if (PointInTriangle(A, C, D, P))
		return true;
	return false;
}

bool Collider::PointInTriangle(const Vector2 &A, const Vector2 &B,
		const Vector2 &C, const Vector2 &P) {

	// Compute vectors
	Vector2 v0 = C - A;
	Vector2 v1 = B - A;
	Vector2 v2 = P - A;

	// Compute dot products
	float dot00 = v0 * v0;
	float dot01 = v0 * v1;
	float dot02 = v0 * v2;
	float dot11 = v1 * v1;
	float dot12 = v1 * v2;

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	if (u >= 0 && v >= 0 && (u + v) < 1) {
		return true;
	} else {
		return false;
	}
}

bool Collider::collides(const Vector2 &o1Pos, float o1Width, float o1Height,
		const Vector2 &o2Pos, float o2Width, float o2Height) {

	// o1 completely to the left of o2, or vice versa
	if (o1Pos.getX() + o1Width < o2Pos.getX()
			|| o2Pos.getX() + o2Width < o1Pos.getX()) {
		return false;
	}

	// o1 completely to the top of o2, or vice versa
	if (o1Pos.getY() + o1Height < o2Pos.getY()
			|| o2Pos.getY() + o2Height < o1Pos.getY()) {
		return false;
	}

	return true;
}