internal void
SimulateTextInputs(Input* input, TextInput text) {
	LARGE_INTEGER time_start;
	QueryPerformanceCounter(&time_start);
	if (is_down(BUTTON_A) && is_down(BUTTON_SHIFT) && (!a.GetHeld())) {
		a.SetHeld(true);
		text.AddText("A");		
	}
	else if (is_down(BUTTON_A) && (!a.GetHeld())) {
		a.SetHeld(true);
		text.AddText("a");
		
	}
	else if (!is_down(BUTTON_A)) {
		a.SetHeld(false);
	}

	if (is_down(BUTTON_B) && is_down(BUTTON_SHIFT) && (!b.GetHeld())) {
		text.AddText("B");
		b.SetHeld(true);
	}
	else if (is_down(BUTTON_B) && (!b.GetHeld())) {
		text.AddText("b");
		b.SetHeld(true);
	}
	else if (!is_down(BUTTON_B)) {
		b.SetHeld(false);
	}

	if (is_down(BUTTON_C) && is_down(BUTTON_SHIFT) && (!c.GetHeld())) {
		text.AddText("C");
		c.SetHeld(true);
	}
	else if (is_down(BUTTON_C) && (!c.GetHeld())) {
		text.AddText("c");
		c.SetHeld(true);
	}
	else if (!is_down(BUTTON_C)) {
		c.SetHeld(false);
	}

	if (is_down(BUTTON_D) && is_down(BUTTON_SHIFT) && (!d.GetHeld())) {
		text.AddText("D");
		d.SetHeld(true);
	}
	else if (is_down(BUTTON_D) && (!d.GetHeld())) {
		text.AddText("d");
		d.SetHeld(true);
	}
	else if (!is_down(BUTTON_D)) {
		d.SetHeld(false);
	}

	if (is_down(BUTTON_E) && is_down(BUTTON_SHIFT) && (!e.GetHeld())) {
		text.AddText("E");
		e.SetHeld(true);
	}
	else if (is_down(BUTTON_E) && (!e.GetHeld())) {
		text.AddText("e");
		e.SetHeld(true);
	}
	else if (!is_down(BUTTON_E)) {
		e.SetHeld(false);
	}

	if (is_down(BUTTON_F) && is_down(BUTTON_SHIFT) && (!f.GetHeld())) {
		text.AddText("F");
		f.SetHeld(true);
	}
	else if (is_down(BUTTON_F) && (!f.GetHeld())) {
		text.AddText("f");
		f.SetHeld(true);
	}
	else if (!is_down(BUTTON_F)) {
		f.SetHeld(false);
	}

	if (is_down(BUTTON_G) && is_down(BUTTON_SHIFT) && (!g.GetHeld())) {
		text.AddText("G");
		g.SetHeld(true);
	}
	else if (is_down(BUTTON_G) && (!g.GetHeld())) {
		text.AddText("g");
		g.SetHeld(true);
	}
	else if (!is_down(BUTTON_G)) {
		g.SetHeld(false);
	}

	if (is_down(BUTTON_H) && is_down(BUTTON_SHIFT) && (!h.GetHeld())) {
		text.AddText("H");
		h.SetHeld(true);
	}
	else if (is_down(BUTTON_H) && (!h.GetHeld())) {
		text.AddText("h");
		h.SetHeld(true);
	}
	else if (!is_down(BUTTON_H)) {
		h.SetHeld(false);
	}

	if (is_down(BUTTON_I) && is_down(BUTTON_SHIFT) && (!i.GetHeld())) {
		text.AddText("I");
		i.SetHeld(true);
	}
	else if (is_down(BUTTON_I) && (!i.GetHeld())) {
		text.AddText("i");
		i.SetHeld(true);
	}
	else if (!is_down(BUTTON_I)) {
		i.SetHeld(false);
	}

	if (is_down(BUTTON_J) && is_down(BUTTON_SHIFT) && (!j.GetHeld())) {
		text.AddText("J");
		j.SetHeld(true);
	}
	else if (is_down(BUTTON_J) && (!j.GetHeld())) {
		text.AddText("j");
		j.SetHeld(true);
	}
	else if (!is_down(BUTTON_J)) {
		j.SetHeld(false);
	}

	if (is_down(BUTTON_K) && is_down(BUTTON_SHIFT) && (!k.GetHeld())) {
		text.AddText("K");
		k.SetHeld(true);
	}
	else if (is_down(BUTTON_K) && (!k.GetHeld())) {
		text.AddText("k");
		k.SetHeld(true);
	}
	else if (!is_down(BUTTON_K)) {
		k.SetHeld(false);
	}

	if (is_down(BUTTON_L) && is_down(BUTTON_SHIFT) && (!l.GetHeld())) {
		text.AddText("L");
		l.SetHeld(true);
	}
	else if (is_down(BUTTON_L) && (!l.GetHeld())) {
		text.AddText("l");
		l.SetHeld(true);
	}
	else if (!is_down(BUTTON_L)) {
		l.SetHeld(false);
	}

	if (is_down(BUTTON_M) && is_down(BUTTON_SHIFT) && (!m.GetHeld())) {
		text.AddText("M");
		m.SetHeld(true);
	}
	else if (is_down(BUTTON_M) && (!m.GetHeld())) {
		text.AddText("m");
		m.SetHeld(true);
	}
	else if (!is_down(BUTTON_M)) {
		m.SetHeld(false);
	}

	if (is_down(BUTTON_N) && is_down(BUTTON_SHIFT) && (!n.GetHeld())) {
		text.AddText("N");
		n.SetHeld(true);
	}
	else if (is_down(BUTTON_N) && (!n.GetHeld())) {
		text.AddText("n");
		n.SetHeld(true);
	}
	else if (!is_down(BUTTON_N)) {
		n.SetHeld(false);
	}

	if (is_down(BUTTON_O) && is_down(BUTTON_SHIFT) && (!o.GetHeld())) {
		text.AddText("O");
		o.SetHeld(true);
	}
	else if (is_down(BUTTON_O) && (!o.GetHeld())) {
		text.AddText("o");
		o.SetHeld(true);
	}
	else if (!is_down(BUTTON_O)) {
		o.SetHeld(false);
	}

	if (is_down(BUTTON_P) && is_down(BUTTON_SHIFT) && (!p.GetHeld())) {
		text.AddText("P");
		p.SetHeld(true);
	}
	else if (is_down(BUTTON_P) && (!p.GetHeld())) {
		text.AddText("p");
		p.SetHeld(true);
	}
	else if (!is_down(BUTTON_P)) {
		p.SetHeld(false);
	}

	if (is_down(BUTTON_Q) && is_down(BUTTON_SHIFT) && (!q.GetHeld())) {
		text.AddText("Q");
		q.SetHeld(true);
	}
	else if (is_down(BUTTON_Q) && (!q.GetHeld())) {
		text.AddText("q");
		q.SetHeld(true);
	}
	else if (!is_down(BUTTON_Q)) {
		q.SetHeld(false);
	}

	if (is_down(BUTTON_R) && is_down(BUTTON_SHIFT) && (!r.GetHeld())) {
		text.AddText("R");
		r.SetHeld(true);
	}
	else if (is_down(BUTTON_R) && (!r.GetHeld())) {
		text.AddText("r");
		r.SetHeld(true);
	}
	else if (!is_down(BUTTON_R)) {
		r.SetHeld(false);
	}

	if (is_down(BUTTON_S) && is_down(BUTTON_SHIFT) && (!s.GetHeld())) {
		text.AddText("S");
		s.SetHeld(true);
	}
	else if (is_down(BUTTON_S) && (!s.GetHeld())) {
		text.AddText("s");
		s.SetHeld(true);
	}
	else if (!is_down(BUTTON_S)) {
		s.SetHeld(false);
	}

	if (is_down(BUTTON_T) && is_down(BUTTON_SHIFT) && (!t.GetHeld())) {
		text.AddText("T");
		t.SetHeld(true);
	}
	else if (is_down(BUTTON_T) && (!t.GetHeld())) {
		text.AddText("t");
		t.SetHeld(true);
	}
	else if (!is_down(BUTTON_T)) {
		t.SetHeld(false);
	}

	if (is_down(BUTTON_U) && is_down(BUTTON_SHIFT) && (!u.GetHeld())) {
		text.AddText("U");
		u.SetHeld(true);
	}
	else if (is_down(BUTTON_U) && (!u.GetHeld())) {
		text.AddText("u");
		u.SetHeld(true);
	}
	else if (!is_down(BUTTON_U)) {
		u.SetHeld(false);
	}

	if (is_down(BUTTON_V) && is_down(BUTTON_SHIFT) && (!v.GetHeld())) {
		text.AddText("V");
		v.SetHeld(true);
	}
	else if (is_down(BUTTON_V) && (!v.GetHeld())) {
		text.AddText("v");
		v.SetHeld(true);
	}
	else if (!is_down(BUTTON_V)) {
		v.SetHeld(false);
	}

	if (is_down(BUTTON_W) && is_down(BUTTON_SHIFT) && (!w.GetHeld())) {
		text.AddText("W");
		w.SetHeld(true);
	}
	else if (is_down(BUTTON_W) && (!w.GetHeld())) {
		text.AddText("w");
		w.SetHeld(true);
	}
	else if (!is_down(BUTTON_W)) {
		w.SetHeld(false);
	}

	if (is_down(BUTTON_X) && is_down(BUTTON_SHIFT) && (!x.GetHeld())) {
		text.AddText("X");
		x.SetHeld(true);
	}
	else if (is_down(BUTTON_X) && (!x.GetHeld())) {
		text.AddText("x");
		x.SetHeld(true);
	}
	else if (!is_down(BUTTON_X)) {
		x.SetHeld(false);
	}

	if (is_down(BUTTON_Y) && is_down(BUTTON_SHIFT) && (!y.GetHeld())) {
		text.AddText("Y");
		y.SetHeld(true);
	}
	else if (is_down(BUTTON_Y) && (!y.GetHeld())) {
		text.AddText("y");
		y.SetHeld(true);
	}
	else if (!is_down(BUTTON_Y)) {
		y.SetHeld(false);
	}

	if (is_down(BUTTON_Z) && is_down(BUTTON_SHIFT) && (!z.GetHeld())) {
		text.AddText("Z");
		z.SetHeld(true);
	}
	else if (is_down(BUTTON_Z) && (!z.GetHeld())) {
		text.AddText("z");
		z.SetHeld(true);
	}
	else if (!is_down(BUTTON_Z)) {
		z.SetHeld(false);
	}

	if (is_down(BUTTON_0) && (!zero.GetHeld())) {
		text.AddText("0");
		zero.SetHeld(true);
	}
	else if (!is_down(BUTTON_0)) {
		zero.SetHeld(false);
	}

	if (is_down(BUTTON_1) && (!one.GetHeld())) {
		text.AddText("1");
		one.SetHeld(true);
	}
	else if (!is_down(BUTTON_1)) {
		one.SetHeld(false);
	}

	if (is_down(BUTTON_2) && (!two.GetHeld())) {
		text.AddText("2");
		two.SetHeld(true);
	}
	else if (!is_down(BUTTON_2)) {
		two.SetHeld(false);
	}

	if (is_down(BUTTON_3) && (!three.GetHeld())) {
		text.AddText("3");
		three.SetHeld(true);
	}
	else if (!is_down(BUTTON_3)) {
		three.SetHeld(false);
	}

	if (is_down(BUTTON_4) && (!four.GetHeld())) {
		text.AddText("4");
		four.SetHeld(true);
	}
	else if (!is_down(BUTTON_4)) {
		four.SetHeld(false);
	}

	if (is_down(BUTTON_5) && (!five.GetHeld())) {
		text.AddText("5");
		five.SetHeld(true);
	}
	else if (!is_down(BUTTON_5)) {
		five.SetHeld(false);
	}

	if (is_down(BUTTON_6) && (!six.GetHeld())) {
		text.AddText("6");
		six.SetHeld(true);
	}
	else if (!is_down(BUTTON_6)) {
		six.SetHeld(false);
	}

	if (is_down(BUTTON_7) && (!seven.GetHeld())) {
		text.AddText("7");
		seven.SetHeld(true);
	}
	else if (!is_down(BUTTON_7)) {
		seven.SetHeld(false);
	}

	if (is_down(BUTTON_8) && (!eight.GetHeld())) {
		text.AddText("8");
		eight.SetHeld(true);
	}
	else if (!is_down(BUTTON_8)) {
		eight.SetHeld(false);
	}

	if (is_down(BUTTON_9) && (!nine.GetHeld())) {
		text.AddText("9");
		nine.SetHeld(true);
	}
	else if (!is_down(BUTTON_9)) {
		nine.SetHeld(false);
	}

	if (is_down(BUTTON_BACKSPACE) && (!back.GetHeld())) {
		text.RemoveText();
		back.SetHeld(true);
	}
	else if (!is_down(BUTTON_BACKSPACE)) {
		back.SetHeld(false);
	}

	LARGE_INTEGER time_end;
	QueryPerformanceCounter(&time_end);
	float dt = (float)time_end.QuadPart - (float)time_start.QuadPart;
}

const char numbers[10] = 
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char letters[52] = 
{ 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 
'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 
'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z' };

