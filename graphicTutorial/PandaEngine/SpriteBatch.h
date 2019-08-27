#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace PandaEngine {


	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph
	{ 
	public:

		Glyph(); 

		Glyph(const glm::vec4 & dectRect, const glm::vec4 & uvRect, GLuint TextureId, float Depth, const ColorRGBA8 & color)
			:textureId(TextureId),depth(Depth)
		{  
		     topLeft.color = color;
		     topLeft.setPosition(dectRect.x, dectRect.y + dectRect.w);
		     topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		     
		     bottomLeft.color = color;
		     bottomLeft.setPosition(dectRect.x, dectRect.y);
		     bottomLeft.setUV(uvRect.x, uvRect.y);
		     
		     bottomRight.color = color;
		     bottomRight.setPosition(dectRect.x + dectRect.z, dectRect.y);
		     bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		     
		     topRight.color = color;
		     topRight.setPosition(dectRect.x + dectRect.z, dectRect.y + dectRect.w);
		     topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

		GLuint textureId;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint TextureId) :offset(Offset), numVertices(NumVertices), textureId(TextureId)
		{

		}
		
		GLuint offset;
		GLuint numVertices;
		GLuint textureId;

	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		void end();

		void draw(const glm::vec4& dectRect, const glm::vec4& uvRect, GLuint textureId, float depth, const ColorRGBA8& color);

		void renderbatch();

	private:

		void createRenderBatchs();
		void createvertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;
		
		GlyphSortType _sortType;

		std::vector<Glyph> _glyphs; // These are the actual glyphs
		std::vector<Glyph*> _glyphPointer; // this is for sorting 

		std::vector<RenderBatch> _renderbatchs;
	};
}
#endif // !SPRITEBATCH_H

