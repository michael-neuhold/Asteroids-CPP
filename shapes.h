#pragma once
#include <ml5/ml5.h>

struct shape : ml5::object {
	using context = ml5::paint_event::context_t;
	shape(wxPoint point, const wxPen& pen, const wxBrush& brush);

	void draw(context& con);
	auto contains(wxPoint pos) const noexcept -> bool;
	auto empty() const noexcept -> bool;
	void set_right_bottom(wxPoint point);
	void move(wxPoint offset);
	void set_pen(const wxPen &pen);
	void set_brush(const wxBrush &brush);
	virtual std::unique_ptr<shape> create_copy() = 0;

	wxRect aabb;
	wxPen pen;
	wxBrush brush;

private:
	virtual void draw_(context&) const = 0;
	
};

/* ============= line ============ */

struct line final : shape {
	using shape::shape;
	std::unique_ptr<shape> create_copy();
private:
	void draw_(context& cont) const override;
};

/* ============= ellipse ============ */

struct ellipse final : shape {
	using shape::shape;
	std::unique_ptr<shape> create_copy();
private:
	void draw_(context& cont) const override;
};

/* ============= rectangle ============ */

struct rectangle final : shape {
	using shape::shape;
	std::unique_ptr<shape> create_copy();
private:
	void draw_(context& cont) const override;
};