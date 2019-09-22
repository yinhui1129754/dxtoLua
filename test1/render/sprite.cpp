#include "../stdafx.h"
#include "sprite.h"



sprite::sprite()
{
	this->init();
	this->spriteType = "box";
}
sprite::sprite(char * url,content * cc) {
	this->init();
	this->img = cc->getSoucre(url);
	this->width = (float)this->img->GetSize().width;
	this->height = (float)this->img->GetSize().height;
};
void sprite::initOneFrame(float w, float h,int f) {
	this->width = w;
	this->height = h;
	this->frame = new D2D1_RECT_F();
	this->frame->left = f*w;
	this->frame->top = 0;
	this->frame->right = w;
	this->frame->bottom = h;
};
sprite::sprite(ID2D1Bitmap * url , float w2, float h2, string spriteType) {
	this->init();
	this->img = url;
	if (w2 == -1.0f) {
		this->width = (float)this->img->GetSize().width;
	}
	else {
		this->width = w2;
	}
	if (h2 == -1.0f) {
		this->height = (float)this->img->GetSize().height;
	}
	else {
		this->height = h2;
	}
}
sprite::sprite(ID2D1Bitmap * url,float x,float y,float w2, float h2) {
	this->init();
	this->img = url;
	this->setX(x);
	this->setY(y);
	if (w2 == -1.0f) {
		this->width = (float)this->img->GetSize().width;
	}
	else {
		this->width = w2;
	}
	if (h2 == -1.0f) {
		this->height = (float)this->img->GetSize().height;
	}
	else {
		this->height = h2;
	}
}
void sprite::init() {
	this->g_x = this->x;
	this->g_y = this->y;
	this->pivot.x = 0.5;
	this->pivot.y = 0.5;
	this->zoom.x = 1.0f;
	this->zoom.y = 1.0f;

	this->visible = TRUE;
	this->frame = NULL;
	this->fillSrcX = 0;
	this->fillSrcY = 0;
	this->renderTranPoint = FALSE;
}
void sprite::initG_x() {
	if (this->parent == NULL) {
		this->g_x = this->x;
	}
	else {
		this->g_x = this->parent->g_x + this->x;
	}
	for (unsigned int i = 0; i < this->children.size(); i++) {
		this->children[i]->initG_x();
	}
};
void sprite::initG_y() {
	if (this->parent == NULL) {
		this->g_y = this->y;
	}
	else {
		this->g_y = this->parent->g_y + this->y;
	}

	for (unsigned int i = 0; i < this->children.size(); i++) {
		this->children[i]->initG_y();
	}
};
int sprite::addChild(sprite * child) {
	child->parent = (sprite*)this;
	this->children.push_back(child);
	child->initG_x();
	child->initG_y();

	return this->children.size();
}
int sprite::addChild(sprite * child,BOOL bl) {
	
	child->parent = (sprite*)this;
	if (bl == TRUE) {
		this->children.insert(this->children.begin(),child);
	}
	else {
		this->children.push_back(child);
	}
	child->initG_x();
	child->initG_y();
	return this->children.size();
}
void sprite::setId(string id) {
	this->id = id;
}
BOOL sprite::inRect(POINT * mouse) {
	return (mouse->x >= this->g_x&&mouse->x <= this->g_x + this->getWidth() && mouse->y > this->g_y&&mouse->y <= this->g_y + this->getHeight());
}
sprite * sprite::getChildById(string id) {
	for (unsigned int i = 0; i < this->children.size(); i++) {
		if (this->children[i]->id == id) {
			return this->children[i];
		}
	}
	return NULL;
}
int sprite::removeChild(sprite * child) {
	vector<sprite *>::iterator it = find(this->children.begin(), this->children.end(), child);
	if (it == this->children.end()) {

		return this->children.size();
	}
	this->children.erase(it);
	if (child->parent != NULL) {
		child->parent = NULL;
	}
	return this->children.size();
}
float sprite::getWidth() {
	return this->width*this->zoom.x;
}
float sprite::getHeight() {
	return this->height*this->zoom.y;
}

void sprite::setX(float x) {

	this->x = x;
	this->initG_x();

}
void sprite::setY(float y) {

	this->y = y;
	this->initG_y();

}

sprite::~sprite()
{

}
void sprite::initFrame() {
	this->initFrame(0, 0, this->width, this->height);
}
void sprite::initFrame(float left, float top, float right, float bottom) {
	if (this->frame != NULL) {
		delete this->frame;
		this->frame = NULL;
	}
	this->frame = new D2D1_RECT_F();
	this->frame->bottom = bottom;
	this->frame->top = top;
	this->frame->left = left;
	this->frame->right = right;
}
void sprite::render(winClass * app) {
	if ((LONG)this == 0xDDDDDDDD||!this->visible||this==NULL) {
		return;
	}
	if (this->spriteType == "animateSprite") {
		unsigned int len = this->frameArr.size();
		if (this->speedNowTime + app->msTime >= this->speedTime) {
			this->speedNowTime = 0;
			if (this->nowFrame < len - 1) {
				this->nowFrame++;
			}
			else {
				if (this->loop > 0) {
					this->loop--;
				}
				if (this->loop == 0) {
					this->amtEnd(this);
				}
				else {
					this->nowFrame = 0;
				}

			}
		}
		else {
			this->speedNowTime += app->msTime;
		}
		if (len >= 0) {

			this->frame = &(this->frameArr[this->nowFrame]);

		}
		else {
			this->frame = NULL;
		}
	}
	float x1 = 0.0f;
	float y1 = 0.0f;
	//绘制自己的变换情况
	app->cContent->save();
	if (this->angle != 0) {
		app->cContent->rotate(this->angle, this->g_x + this->getWidth()*this->pivot.x, this->g_y + this->getHeight()*this->pivot.y);
	}


	if (this->frame != NULL) {

		app->cContent->drawImage(this->img, this->g_x + x1, this->g_y + y1, this->width*this->zoom.x, this->height*this->zoom.y, this->frame);
	}
	else if (this->spriteType == "fillSprite") {
		app->cContent->fillImage(this->img, this->g_x + x1, this->g_y + y1, this->width*this->zoom.x, this->height*this->zoom.y,this->fillSrcX,this->fillSrcY);
	}
	else if (this->spriteType == "drawSprite") {
		this->drawCall(this, app);
	}
	else if (this->spriteType == "box") {
	}
	else {
		app->cContent->drawImage(this->img, this->g_x + x1, this->g_y + y1, this->width*this->zoom.x, this->height*this->zoom.y);
	}
	
	//递归绘制所有子元素
	for (unsigned int i = 0; i < this->children.size(); i++) {
		this->children[i]->render(app);
	}
	app->cContent->restore();
	if (this->renderTranPoint) {
		app->cContent->initPath();
		for (unsigned int q = 0; q < this->transitionPoints.size(); q++) {
			if (q == 0) {
				app->cContent->beginPath(this->transitionPoints[q].x, this->transitionPoints[q].y);
			}
			else {
				app->cContent->addPofloat(this->transitionPoints[q].x, this->transitionPoints[q].y);
			}
			app->cContent->fillArc(this->transitionPoints[q].x, this->transitionPoints[q].y, 3, 3);
		}

		app->cContent->addPofloat(this->transitionPoints[0].x, this->transitionPoints[0].y);
		app->cContent->strokeStyle(0xffffff, 1.0f);
		app->cContent->closePath();
		app->cContent->stroke();
		app->cContent->releasePath();
	}
}
//获取全局坐标点
utils::usePoint sprite::getGlobalPoint(utils::usePoint p) {
	utils::usePoint p2;
	p2.x = p.x*this->width*this->zoom.x + this->g_x;
	p2.y = p.y*this->height*this->zoom.y + this->g_y;
	return p2;
};

void sprite::getTransitionPoints() {
	vector <utils::usePoint>().swap(this->transitionPoints);
	utils::usePoint  rotetePoint = { this->g_x + this->pivot.x*this->getWidth(), this->g_y + this->pivot.y*this->getHeight() };
	for (unsigned int i = 0; i < this->points.size(); i++) {
		float x = 0;
		float y = 0;
		utils::usePoint nowPoint = this->getGlobalPoint(this->points[i]);
		double sinVal = sin(this->angle*M_PI / 180.0f);
		double cosVal = cos(this->angle*M_PI / 180.0f);
		x = rotetePoint.x - ((rotetePoint.x - nowPoint.x)*cosVal - (rotetePoint.y - nowPoint.y)*sinVal);
		y = rotetePoint.y - ((rotetePoint.x - nowPoint.x)*sinVal + (rotetePoint.y - nowPoint.y)*cosVal);
		this->transitionPoints.push_back({ x, y });
	}
};
void sprite::getOneVec() {

	vector <vec2>().swap(this->vecArr);
	vec2 v1;
	vec2 v2;
	if (this->transitionPoints.size() == 0) {
		return;
	}
	for (unsigned int  i = 0; i < this->transitionPoints.size() - 1; i++) {
		v1 = vec2(this->transitionPoints[i]);
		v2 = vec2(this->transitionPoints[i + 1]);
		this->vecArr.push_back(v1.edge(v2).normalize());
	}
	if (this->transitionPoints.size() >= 3) {
		v1 = vec2(this->transitionPoints[this->transitionPoints.size() - 1]);
		v2 = vec2(this->transitionPoints[0]);
		this->vecArr.push_back(v1.edge(v2).normalize());
	}
	else {
		this->vecArr.empty();
	}

}
void sprite::addPoint(utils::usePoint p) {
	this->points.push_back(p);
};
void sprite::initPointToRect() {
	this->addPoint({ 0,0 });
	this->addPoint({ 1,0 });
	this->addPoint({ 1,1 });
	this->addPoint({ 0,1 });
}