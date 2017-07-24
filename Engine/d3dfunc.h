void InitD3DFunc();
void d3d_dot(int x1,int y1, int r, int g, int b, int a);
enum {
	ALIGN_LEFT = 0,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

void InitText();
void SetFont(int nFont, LPSTR pFont, int nFontSize, int nFontBold, int nFontItalic);
void StartText(void);
void EndText(void);
void AAText(int nFont, int x, int y, int nAlign, LPSTR pString);
void SetTextCol(int r, int g, int b, int a);
