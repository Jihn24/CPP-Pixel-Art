//Function to Create Initial Objects in Window//

//Create Colour Buttons//

Button* buttons = new Button[100];

internal Button
GetButton(int index) {
	return buttons[index];
}

internal void
CreateInitialButtons() {
	int index = 0;
	u32 colour_button_width;
	colour_button_width = 0.02 * GetScreenWidth();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			buttons[index].CreateShape(GetScreenWidth() * 3 / 5 + j * colour_button_width, GetScreenHeight() * 1 / 3 + i * colour_button_width, colour_button_width, colour_button_width, 0x000000, true, 0x000000);
			if (i == 1) {
				buttons[index].SetBoxColour(0x990000 + 0x001100 * j);
			}
			else if (i == 0) {
				buttons[index].SetBoxColour(0x990011 + 0x000011 * j);
			}
			else if (i == 2) {
				buttons[index].SetBoxColour(0x119900 + 0x110000 * j);
			}
			else if (i == 3) {
				buttons[index].SetBoxColour(0x009900 + 0x000011 * j);
			}
			else if (i == 5) {
				buttons[index].SetBoxColour(0x000099 + 0x110000 * j);
			}
			else if (i == 4) {
				buttons[index].SetBoxColour(0x001199 + 0x001100 * j);
			}
			else if (i == 6) {
				buttons[index].SetBoxColour(0x000022 + 0x000011 * j);
			}
			else if (i == 7) {
				buttons[index].SetBoxColour(0x002200 + 0x001100 * j);
			}
			else if (i == 8) {
				buttons[index].SetBoxColour(0x220000 + 0x110000 * j);
			}
			else if (i == 9 && j != 9) {
				buttons[index].SetBoxColour(0x000000 + 0x111111 * j);
			}
			else {
				buttons[index].SetBoxColour(0xFFFFFF);
			}
			index++;
		}
	}
}

//End Colour Button Creation// 
//Create Paintbrush Object//

PaintBrush paint_brush;

internal void
CreateBrush() {
	paint_brush.CreateShape(0, 0, 0.01 * screen_width, 0.01 * screen_width, 0xFFFFFF, true, 0x000000);
}

//End Create Paint Brush//
//Create Sliders

Slider red_slider;
Slider green_slider;
Slider blue_slider;
u32 slider_r_width;
u32 slider_r_height;

internal void
CreateInitialSliders() {
	slider_r_width = screen_width * 0.15;
	slider_r_height = slider_r_width * 0.12;

	red_slider.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5 + (slider_r_height * 1.75), slider_r_width, slider_r_height, 0xFF0000, true, 0x000000);
	red_slider.CreateSlider(red_slider.GetPosition_x(), red_slider.GetPosition_y() - (red_slider.GetHeight() / 4), red_slider.GetWidth() * 0.05, red_slider.GetHeight() * 1.5, 0xFF0000, true, 0x000000);

	green_slider.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, slider_r_width, slider_r_height, 0x00FF00, true, 0x000000);
	green_slider.CreateSlider(green_slider.GetPosition_x(), green_slider.GetPosition_y() - (green_slider.GetHeight() / 4), green_slider.GetWidth() * 0.05, green_slider.GetHeight() * 1.5, 0x00FF00, true, 0x000000);

	blue_slider.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5 - (slider_r_height * 1.75), slider_r_width, slider_r_height, 0x0000FF, true, 0x000000);
	blue_slider.CreateSlider(blue_slider.GetPosition_x(), blue_slider.GetPosition_y() - (blue_slider.GetHeight() / 4), blue_slider.GetWidth() * 0.05, blue_slider.GetHeight() * 1.5, 0x0000FF, true, 0x000000);
}

Button new_colour_box;

internal void
CreateInitialNewColourBoxes() {
	new_colour_box.CreateShape(GetScreenWidth() * 4 / 5, GetScreenHeight() * 1 / 5 - (GetScreenWidth() * 0.02), GetScreenWidth() * 0.05, GetScreenWidth() * 0.05, 0xFFFFFF, true, 0x000000);
}

//End Slider Creation//
//Create Initial Menus// 
Button close_input_button;
Button input_button;
Button save_button;
Button load_button;
Button change_size_button;
Button brush_button;
Button clear_canvas_button;
Button change_background_button;
TextInput input_text_box;
TextInput width_text_box;
Shape width_label;
Shape height_label;
Shape width_x_height;
TextInput height_text_box;

u32 standard_box_width;
u32 standard_box_height;

internal void
CreateInitialTextMenus() {
	standard_box_width = GetScreenWidth() * 0.12;
	standard_box_height = standard_box_width * 0.25;

	save_button.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 4 / 5, standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	save_button.AddBoxText({ "SAVE" }, 0x000000, standard_box_width * 0.03, "LEFT", save_button.GetWidth() * 0.05, "CENTRE", save_button.GetHeight() * 0.3);

	load_button.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 4 / 5 - (standard_box_height * 1.25), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	load_button.AddBoxText({ "LOAD" }, 0x000000, standard_box_width * 0.03, "LEFT", load_button.GetWidth() * 0.05, "CENTRE", load_button.GetHeight() * 0.3);

	change_size_button.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 4 / 5 + (standard_box_height * 1.25), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	change_size_button.AddBoxText({ "RESIZE" }, 0x000000, standard_box_width * 0.03, "LEFT", change_size_button.GetWidth() * 0.05, "CENTRE", change_size_button.GetHeight() * 0.3);

	brush_button.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5 + (standard_box_height * 1.25), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	brush_button.AddBoxText({ "BRUSH" }, 0x000000, standard_box_width * 0.03, "LEFT", brush_button.GetWidth() * 0.05, "CENTRE", brush_button.GetHeight() * 0.3);

	change_background_button.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5 + (standard_box_height * 2.5), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	change_background_button.AddBoxText({ "BACKGROUND" }, 0x000000, standard_box_width * 0.0195, "LEFT", change_background_button.GetWidth() * 0.05, "CENTRE", change_background_button.GetHeight() * 0.3);

	clear_canvas_button.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 4 / 5 + (standard_box_height * 2.5), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	clear_canvas_button.AddBoxText({ "CLEAR" }, 0x000000, standard_box_width * 0.03, "LEFT", clear_canvas_button.GetWidth() * 0.05, "CENTRE", clear_canvas_button.GetHeight() * 0.3);
	
	input_text_box.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5 - (standard_box_height * 1.25), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	input_text_box.AddBoxText({ "", "" }, 0x000000, standard_box_width * 0.03, "LEFT", input_text_box.GetWidth() * 0.05, "BOTTOM", standard_box_height * 1.4);

	height_text_box.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5 - (standard_box_height * 1.25), standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	height_text_box.AddBoxText({ "" }, 0x000000, standard_box_width * 0.03, "LEFT", height_text_box.GetWidth() * 0.05, "CENTRE", 0);

	width_text_box.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5, standard_box_width, standard_box_height, 0xFFFFFF, true, 0x000000);
	width_text_box.AddBoxText({ "" }, 0x000000, standard_box_width * 0.03, "LEFT", width_text_box.GetWidth() * 0.05, "CENTRE", 0);

	input_button.CreateShape(input_text_box.GetPosition_x(), input_text_box.GetPosition_y() - input_text_box.GetHeight() * 0.3, input_text_box.GetWidth() * 0.15, input_text_box.GetHeight() * 0.3, 0x00FF00, true, 0x000000);

	close_input_button.CreateShape(input_text_box.GetPosition_x() + input_text_box.GetWidth() - input_text_box.GetWidth() * 0.15, input_text_box.GetPosition_y() - input_text_box.GetHeight() * 0.3, input_text_box.GetWidth() * 0.15, input_text_box.GetHeight() * 0.3, 0xFF0000, true, 0x000000);
	
	width_label.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2.25), GetScreenHeight() * 4 / 5, standard_box_width, standard_box_height, 0x000000, false, 0x000000);
	width_label.AddBoxText({ "Width" }, 0x000000, standard_box_width * 0.03, "LEFT", standard_box_width * 0.1, "CENTRE", 0);
	width_label.HideBox();

	height_label.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2.25), GetScreenHeight() * 4 / 5 - (standard_box_height * 1.25), standard_box_width, standard_box_height, 0x000000, false, 0x000000);
	height_label.AddBoxText({ "Height" }, 0x000000, standard_box_width * 0.03, "LEFT", standard_box_width * 0.1, "CENTRE", 0);
	height_label.HideBox();

	width_x_height.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.25), GetScreenHeight() * 4 / 5 - (standard_box_height * 0.65), standard_box_width, standard_box_height, 0xFFFFFF, false, 0x000000);
	width_x_height.AddBoxText({ "X" }, 0x000000, standard_box_width * 0.015, "CENTRE", 0, "CENTRE", 0);
	width_x_height.HideBox();
}
//End Initial Menu Creation//
//Create Confirmation Menu//

Shape confirmation_box;
Button confirm;
Button reject;
bool confirmation_open = false;

internal void
SetSaveConfirmationOpen(bool is_open) {
	confirmation_open = is_open;
}
internal bool
GetSaveConfirmationOpen() {
	return confirmation_open;
}

internal void
CreateInitialConfirmation() {
	confirmation_box.CreateShape(GetScreenWidth() * 0.4, GetScreenHeight() * 0.4, GetScreenWidth() * 0.2, GetScreenHeight() * 0.2, 0xFFFFFF, true, 0x000000);
	//confirmation_box.AddBoxText({ "Overwrite", "Save File?" }, 0x000000, 4, "CENTRE", 10, "CENTRE", 10);

	reject.CreateShape(confirmation_box.GetPosition_x() + confirmation_box.GetWidth() * 0.6, confirmation_box.GetPosition_y(), confirmation_box.GetWidth() * 0.4, confirmation_box.GetHeight() * 0.2, 0xFF0000, true, 0x000000);
	reject.AddBoxText({ "NO" }, 0x000000, 2, "CENTRE", 5, "CENTRE", 5);

	confirm.CreateShape(confirmation_box.GetPosition_x(), confirmation_box.GetPosition_y(), confirmation_box.GetWidth() * 0.4, confirmation_box.GetHeight() * 0.2, 0x00FF00, true, 0x000000);
	confirm.AddBoxText({ "YES" }, 0x000000, 2, "CENTRE", 5, "CENTRE", 5);
}

//End Confirmation Menu//
//Create Brush Buttons// 
Button small_brush;
Button medium_circle_brush;
Button large_circle_brush;
Button small_square_brush;
Button medium_square_brush;
Button large_square_brush;
Button straight_line_tool;
Button select_tool;

internal void
CreateBrushOptions() {
	small_brush.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.3), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.01, standard_box_height, 0xFFFFFF, true, 0x000000);
	medium_circle_brush.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 1.6), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.03, standard_box_height, 0xFFFFFF, true, 0x000000);
	large_circle_brush.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.05, standard_box_height, 0xFFFFFF, true, 0x000000);
	medium_square_brush.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2.4), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.03, GetScreenWidth() * 0.03, 0xFFFFFF, true, 0x000000);
	large_square_brush.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2.8), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.05, GetScreenWidth() * 0.05, 0xFFFFFF, true, 0x000000);
	straight_line_tool.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 2), GetScreenHeight() * 4 / 5 - standard_box_height * 1.4, GetScreenWidth() * 0.1, GetScreenHeight() * 0.02, 0xFFFFFF, true, 0x0000000);
	straight_line_tool.AddSprite("line");
	select_tool.CreateShape(GetScreenWidth() * 3 / 5 + (standard_box_width * 3.2), GetScreenHeight() * 4 / 5, GetScreenWidth() * 0.03, GetScreenWidth() * 0.03, 0xFFFFFF, true, 0x000000);
}
//End Brush Buttons//
//Create New Colour Buttons//

Button* user_colour_buttons = new Button[10];

internal Button
GetUserButton(u32 index) {
	return user_colour_buttons[index];
}

internal void
CreateUserColourButtons() {
	u32 colour_button_width = 0.02 * GetScreenWidth();
	for (int index = 0; index < 10; index++) {
		user_colour_buttons[index].CreateShape(GetScreenWidth() * 3 / 5 + index * colour_button_width, GetScreenHeight() * 1 / 13, colour_button_width, colour_button_width, 0xF1F1F1, true, 0x000000);
	}
	user_colour_buttons[5].AddBoxText({ "Right Click to Store Colour" }, 0x000000, 0.003 * GetScreenHeight(), "CENTRE", 0, "BOTTOM", -0.04 * GetScreenHeight());
}

//End New Colour Buttons//
//Create Select Option Buttons//

Button copy_selected;
Button move_selected;
Button delete_selected;
Button save_selected;
Button close_selected;

internal void
CreateSelectOptions() {
	copy_selected.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, GetScreenWidth() * 0.11, standard_box_height, 0xFFFFFF, true, 0x000000);
	move_selected.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, GetScreenWidth() * 0.015, GetScreenWidth() * 0.015, 0xFFFFFF, true, 0x000000);
	delete_selected.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, GetScreenWidth() * 0.11, standard_box_height, 0xFFFFFF, true, 0x000000);
	save_selected.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, GetScreenWidth() * 0.11, standard_box_height, 0xFFFFFF, true, 0x000000);
	close_selected.CreateShape(GetScreenWidth() * 3 / 5, GetScreenHeight() * 1 / 5, GetScreenWidth() * 0.01, GetScreenWidth() * 0.01, 0xFF0000, true, 0x000000);
}

internal void
RenderSelectionBox() {
	MatrixSelection(0, 0, 2);
}

internal void
SetSelectionOptionsPosition() {
	copy_selected.SetPosition_x(max(GetSelectionX2(), GetSelectionX1()) + 6); copy_selected.SetPosition_y(min(GetSelectionY2(), GetSelectionY1()));
	copy_selected.AddBoxText({ "copy" }, 0x000000, 4, "CENTRE", 0, "CENTRE", 0);
	save_selected.SetPosition_x(max(GetSelectionX2(), GetSelectionX1()) + 6); save_selected.SetPosition_y(min(GetSelectionY2(), GetSelectionY1()) + copy_selected.GetHeight());
	save_selected.AddBoxText({ "save" }, 0x000000, 4, "CENTRE", 0, "CENTRE", 0);
	delete_selected.SetPosition_x(max(GetSelectionX2(), GetSelectionX1()) + 6); delete_selected.SetPosition_y(min(GetSelectionY2(), GetSelectionY1()) + copy_selected.GetHeight() * 2);
	delete_selected.AddBoxText({ "delete" }, 0x000000, 4, "CENTRE", 0, "CENTRE", 0);
	move_selected.SetPosition_x(min(GetSelectionX2(), GetSelectionX1())); move_selected.SetPosition_y(min(GetSelectionY2(), GetSelectionY1()));
	move_selected.AddBoxText({ "move" }, 0x000000, 4, "CENTRE", 0, "BOTTOM", -5);
	close_selected.SetPosition_x(max(GetSelectionX2(), GetSelectionX1())); close_selected.SetPosition_y(max(GetSelectionY2(), GetSelectionY1()));
}

internal void
RenderSelectionOptions() {
	copy_selected.RenderBox(false);
	save_selected.RenderBox(false);
	delete_selected.RenderBox(false);
	move_selected.RenderBox(true);
	close_selected.RenderBox(true);
}

//Create all key objects//

Keys a;
Keys b;
Keys c;
Keys d;
Keys e;
Keys f;
Keys g;
Keys h;
Keys i;
Keys j;
Keys k;
Keys l;
Keys m;
Keys n;
Keys o;
Keys p;
Keys q;
Keys r;
Keys s;
Keys t;
Keys u;
Keys v;
Keys w;
Keys x;
Keys y;
Keys z;
Keys zero;
Keys one;
Keys two;
Keys three;
Keys four;
Keys five;
Keys six;
Keys seven;
Keys eight;
Keys nine;
Keys back;
Keys space;


//End Keys Creation//
