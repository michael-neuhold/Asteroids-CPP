#include "shapes.h"

/* =============== shape =============== */

shape::shape(wxPoint point, const wxPen & pen, const wxBrush & brush ) 
	:	aabb{point, point}, 
		pen{pen}, 
		brush{brush} 
	{}

void shape::draw(context & con) {
	con.SetPen(pen);
	con.SetBrush(brush);
	draw_(con);
}

auto shape::contains(wxPoint pos) const noexcept -> bool { 
	return aabb.Contains(pos); 
}

auto shape::empty() const noexcept -> bool { 
	return !aabb.GetWidth() && !aabb.GetHeight(); 
}

void shape::set_right_bottom(wxPoint point) { 
	aabb.SetRightBottom(point); 
}

void shape::move(wxPoint offset) { 
	aabb.Offset(offset); 
}

void shape::set_pen(const wxPen& pen) { 
	this->pen = pen; 
}

void shape::set_brush(const wxBrush& brush) { 
	this->brush = brush; 
}

/* ==================================== */
/* ==================================== */


/* =============== line =============== */

void line::draw_(context& cont) const { 
	cont.DrawLine(aabb.GetLeftTop(), aabb.GetBottomRight()); 
}

std::unique_ptr<shape> line::create_copy() {
	std::unique_ptr<shape> copied_shape = std::make_unique<line>(aabb.GetLeftTop(), pen, brush);
	copied_shape->set_right_bottom(aabb.GetBottomRight());
	return copied_shape;
}


/* =============== ellipse =============== */

void ellipse::draw_(context& cont) const { 
	cont.DrawEllipse(aabb); 
}

std::unique_ptr<shape> ellipse::create_copy() {
	std::unique_ptr<shape> copied_shape = std::make_unique<ellipse>(aabb.GetLeftTop(), pen, brush);
	copied_shape->set_right_bottom(aabb.GetBottomRight());
	return copied_shape;
}


/* =============== rectangle =============== */

void rectangle::draw_(context& cont) const { 
	cont.DrawRectangle(aabb); 
}

std::unique_ptr<shape> rectangle::create_copy() {
	std::unique_ptr<shape> copied_shape = std::make_unique<rectangle>(aabb.GetLeftTop(), pen, brush);
	copied_shape->set_right_bottom(aabb.GetBottomRight());
	return copied_shape;
}