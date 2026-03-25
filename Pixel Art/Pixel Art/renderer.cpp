internal void 
ClearScreen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void 
DrawRectInPixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
DrawRect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	//Change to pixels
	int x0 = x;
	int x1 = x + 2 * half_size_x;
	int y0 = y;
	int y1 = y + 2 * half_size_y;

	DrawRectInPixels(x0, y0, x1, y1, color);
}

internal void
DrawLettersText(vector<string> text_string, u32 x, u32 y, u32 size, u32 colour) {
	float half_size = size / 2;
	float start_y = y;
	float very_start_x = x;
	vector<const char*> text;
	u32 letter_width = 1;
	for (int i = 0; i < text_string.size(); i++) {
		text.push_back(text_string[i].c_str());
	}

	for (int line = 0; line < text.size(); line++) {
		x = very_start_x;

		while (*text[line]) {
			const char** a_letter = numbers_letters_symbols[*text[line] - ' '];
			float start_x = x;
			y -= (9.5 * size * line);
			letter_width = max(letter_width, (strlen(*a_letter)));
			
			for (int i = 0; i < 9; i++) {
				const char* row = a_letter[i];
				while (*row) {
					if (*row == '0') {
						DrawRect(x, y, half_size, half_size, colour);
					}
					x += size;
					row++;
				}
				y -= size;
				x = start_x;
			}
			text[line]++;
			x += size * (letter_width + 1);
			letter_width = 1;
			y = start_y;
		}
	}
}
