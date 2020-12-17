#include <GraphicsLib/Graphics/3DModelLoader/WavefrontOBJ/WavefrontOBJModelLoader.hpp>
#include <GraphicsLib/Graphics/3DModelLoader/WavefrontOBJ/WavefrontOBJMaterialLoader.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/Base/RuntimeError.hpp>

#include <algorithm>
#include <thread>




namespace cg
{
	const auto countSlash = [](const std::string& line)->int
	{
		int slashCount = 0;
		for (auto chara : line)
		{
			if (chara == '/')
			{
				++slashCount;
			}
		}
		return slashCount;
	};

	int WavefrontOBJModelLoader::loadFaceVertexCount(const std::string& line)
	{
		int slashCount = countSlash(line);

		return slashCount / 2;
	}

	wavefrontobj::VertexFormat WavefrontOBJModelLoader::loadVertexFormat(const std::string& line, int faceVertexCount)
	{
		int slashCount = countSlash(line) / faceVertexCount;


		if (slashCount == 0)
		{
			return wavefrontobj::VertexFormat::p;
		}
		else if (slashCount == 1)
		{
			return wavefrontobj::VertexFormat::pt;
		}
		else if (slashCount == 2)
		{
			if (line.find("//") == std::string::npos)
			{
				return wavefrontobj::VertexFormat::pnt;
			}
			else
			{
				return wavefrontobj::VertexFormat::pn;
			}
		}
		else
		{
			throw RUNTIME_ERROR("Failed to load VertexFormat.");
		}
	}

	int WavefrontOBJModelLoader::loadPositionDimensionCount(const std::string& line)
	{
		auto length = static_cast<int>(line.size());

		int dimensionCount = 0;
		char current = line[0];
		char next;
		for (int i = 0; i < length - 1; ++i)
		{
			const auto index = i+1;
			next = line[index];
			if (current == ' ' && next != ' ')
			{
				dimensionCount += 1;
			}
			current = next;
		}

		return dimensionCount;
	}

	bool WavefrontOBJModelLoader::loadNotation(const std::string& line)
	{
		for (auto chara : line)
		{
			if (chara == '+' || chara == '-')
			{
				return true;
			}
		}

		return false;
	}

	wavefrontobj::Normal3 WavefrontOBJModelLoader::loadNormal3(const std::string& line, bool leftHanded, bool isExpNotation)
	{
		auto normal = WavefrontOBJLoadingHelper::loadVector<float, 3>(line, "vn", " ", true, isExpNotation);
		normal[0] *= leftHanded ? -1.0f : 1.0f;
		return normal;
	}

	wavefrontobj::UV2 WavefrontOBJModelLoader::loadUV2(const std::string& line, bool isExpNotation)
	{
		return WavefrontOBJLoadingHelper::loadVector<float, 2>(line, "vt", " ", true, isExpNotation);
	}

	std::string WavefrontOBJModelLoader::parseLine(cpp::FileStreamInput& fileStream, const std::string& line, const std::string& tag, const std::function<void(const std::string&)>& parseOperation)
	{
		const auto tagLength = static_cast<int>(tag.length());
		auto line_ = line;

		parseOperation(line_);

		while (fileStream.isEOF() == false)
		{
			fileStream.getLine(line_);
			if (line_.empty()) { continue; }
			if (line_[0] == '#') { continue; }

			const auto lineLength = static_cast<int>(line_.length());
			for (int i = 0; i < tagLength; ++i)
			{
				if (lineLength <= i) { return line_; }
				if (tag[i] != line_[i]) { return line_; }
			}
			if (line_[tagLength] != ' ') { return line_; }

			parseOperation(line_);
		}

		return line_;
	}

	std::string WavefrontOBJModelLoader::parseSmoothingGroupLine(cpp::FileStreamInput& fileStream, const std::string& line)
	{
		return parseLine(fileStream, line, "s", [](const std::string&) {});
	}

	std::string WavefrontOBJModelLoader::parseGroupLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* groupName)
	{
		constexpr const char* tag = "g";
		auto load = [&, tag](const std::string& line_)
		{
			*groupName = WavefrontOBJLoadingHelper::loadName(line, tag);
		};

		return parseLine(fileStream, line, tag, load);
	}

	std::string WavefrontOBJModelLoader::parseObjectLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* objectName)
	{
		constexpr const char* tag = "o";
		auto load = [&, tag](const std::string& line_)
		{
			*objectName = WavefrontOBJLoadingHelper::loadName(line, tag);
		};

		return parseLine(fileStream, line, tag, load);
	}

	std::string WavefrontOBJModelLoader::parseMaterialLibLine(cpp::FileStreamInput& fileStream, const std::string& line, cg::wavefrontobj::MaterialDict* materialDict)
	{
		auto load = [&](const std::string& line_)
		{
			*materialDict = loadMaterial(line);
		};

		return parseLine(fileStream, line, "mtllib", load);
	}

	std::string WavefrontOBJModelLoader::parseUseMaterialLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* materialKey)
	{
		auto load = [&](const std::string& line_)
		{
			*materialKey = loadMaterialKey(line_);
		};

		return parseLine(fileStream, line, "usemtl", load);
	}

	std::string WavefrontOBJModelLoader::parsePositionLine(cpp::FileStreamInput& fileStream, const std::string& line, bool leftHanded, wavefrontobj::VertexDataPool* vertexDataPool, int* positionDimensionCount)
	{
		*positionDimensionCount = loadPositionDimensionCount(line);
		const auto isExpNotation = loadNotation(line);

		auto parse = [&](const std::string& line_)
		{
			if (*positionDimensionCount == 3)
			{
				vertexDataPool->position3DataPool.add(loadPosition<3>(line_, leftHanded, isExpNotation));
			}
			else if (*positionDimensionCount == 4)
			{
				vertexDataPool->position4DataPool.add(loadPosition<4>(line_, leftHanded, isExpNotation));
			}
		};
		return parseLine(fileStream, line, "v", parse);
	}

	std::string WavefrontOBJModelLoader::parseNormalLine(cpp::FileStreamInput& fileStream, const std::string& line, bool leftHanded, wavefrontobj::VertexDataPool* vertexDataPool)
	{
		auto isExpNotation = loadNotation(line);

		auto parse = [&](const std::string& line_)
		{
			vertexDataPool->normal3DataPool.add(loadNormal3(line_, leftHanded, isExpNotation));
		};
		return parseLine(fileStream, line, "vn", parse);
	}

	std::string WavefrontOBJModelLoader::parseUVLine(cpp::FileStreamInput& fileStream, const std::string& line, wavefrontobj::VertexDataPool* vertexDataPool)
	{
		auto isExpNotation = loadNotation(line);

		auto parse = [&](const std::string& line_)
		{
			vertexDataPool->uv2DataPool.add(loadUV2(line, isExpNotation));
		};
		return parseLine(fileStream, line, "vt", parse);
	}

	void WavefrontOBJModelLoader::initializationForFaceLineParsing(wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, std::shared_ptr<void>* outVertices, std::shared_ptr<void>* outTriangles, wavefrontobj::Indices* outIndices, unsigned int* outBaseIndex, unsigned int* outVertexCount, unsigned int* outTriangleCount, int* outVertexByteSize, FaceLineParser* outFaceLineParser)
	{
		if (positionDimensionCount == 3)
		{
			switch (vertexFormat)
			{
			case wavefrontobj::VertexFormat::p:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition3>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pt:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition3UV2>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pn:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition3Normal3>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pnt:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition3Normal3UV2>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			}
		}
		else if (positionDimensionCount == 4)
		{
			switch (vertexFormat)
			{
			case wavefrontobj::VertexFormat::p:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition4>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pt:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition4UV2>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pn:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition4Normal3>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			case wavefrontobj::VertexFormat::pnt:
				createResourceForFaceLineParsing<wavefrontobj::VertexPosition4Normal3UV2>(outVertices, outTriangles, outVertexByteSize, outFaceLineParser);
				break;
			}
		}

		*outBaseIndex += *outVertexCount;
		*outVertexCount = 0;
		*outTriangleCount = 0;
		
		outIndices->clear();
	}

	std::vector<wavefrontobj::Index> WavefrontOBJModelLoader::loadFaceIndex(const std::string& line, wavefrontobj::VertexFormat vertexFormat, int faceVertexCount, bool leftHanded)
	{
		std::vector<wavefrontobj::Index> indices;

		auto pBlank = &line[0];
		for (int i = 0; i < faceVertexCount; ++i)
		{
			wavefrontobj::Index index;

			pBlank = strchr(pBlank, ' ') + 1;

			switch (vertexFormat)
			{
			case wavefrontobj::VertexFormat::pnt:
				{
					const auto xy = WavefrontOBJLoadingHelper::loadVector<unsigned int, 3>(pBlank, "", "/", false);
					index.vertex = xy[0];
					index.uv = xy[1];
					index.normal = xy[2];
				}
				break;
			case wavefrontobj::VertexFormat::pn:
				{
					const auto xy = WavefrontOBJLoadingHelper::loadVector<unsigned int, 2>(pBlank, "", "//", false);
					index.vertex = xy[0];
					index.normal = xy[1];
				}
				break;
			case wavefrontobj::VertexFormat::pt:
				{
					const auto xy = WavefrontOBJLoadingHelper::loadVector<unsigned int, 2>(pBlank, "", "/", false);
					index.vertex = xy[0];
					index.uv = xy[1];
				}
				break;
			case wavefrontobj::VertexFormat::p:
				{
					const auto xy = WavefrontOBJLoadingHelper::loadVector<unsigned int, 1>(pBlank, "", "", false);
					index.vertex = xy[0];
				}
				break;
			default:
				Assert(false, "The given VertexFormat is not supported.");
				break;
			}

			--index.vertex;
			--index.normal;
			--index.uv;

			if (leftHanded)
			{
				indices.insert(indices.begin(), index);
			}
			else
			{
				indices.emplace_back(index);
			}
		}
		return indices;
	}
	std::string WavefrontOBJModelLoader::loadMaterialKey(const std::string& line)
	{
		return WavefrontOBJLoadingHelper::loadName(line, "usemtl");
	}

	wavefrontobj::MaterialDict WavefrontOBJModelLoader::loadMaterial(const std::string& line)
	{
		std::string mtlFilename = WavefrontOBJLoadingHelper::loadName(line, "mtllib");
		return wavefrontobj::MaterialLoader::load(mtlFilename);
	}

	std::shared_ptr<WavefrontOBJModel> WavefrontOBJModelLoader::load(const std::string& filename, bool leftHanded)
	{
		cpp::FileStreamInput fileStreamInput(filename);





		wavefrontobj::VertexFormat vertexFormat = wavefrontobj::VertexFormat::p;
		FaceLineParser parseFaceLine;
		int vertexByteSize = 0;
		unsigned int vertexCount = 0;
		unsigned int triangleCount = 0;
		int positionDimensionCount = 0;
		unsigned int baseIndex = 0;
		std::string groupName;
		wavefrontobj::MaterialDict materialDict;
		std::string materialKey;
		auto material = [&](){ return materialDict.count(materialKey) ? materialDict[materialKey] : wavefrontobj::Material(); };
		bool shouldInitialize = true;
		wavefrontobj::Indices indices;
		std::shared_ptr<void> vertices;
		std::shared_ptr<void> triangles;
		wavefrontobj::VertexDataPool vertexDataPool;
		auto group = [&]() { return WavefrontOBJModel::Group(groupName, vertexFormat, positionDimensionCount, vertexCount, triangleCount, vertexByteSize, vertices, triangles, indices, material()); };

		constexpr auto inf = std::numeric_limits<float>::infinity();
		auto model = std::make_shared<WavefrontOBJModel>();
		cpp::Vector3D<float> maxXYZ = { -inf };
		auto& minXYZRef = const_cast<cpp::Vector3D<float>&>(model->minXYZ) = { inf };
		auto& sizeRef = const_cast<cpp::Vector3D<float>&>(model->size);
		auto& groupListRef = const_cast<WavefrontOBJModel::GroupList&>(model->groupList);
		




		std::string line;

		while (fileStreamInput.isEOF() == false)
		{
			if (line.empty()) 
			{
				fileStreamInput.getLine(line);
				continue; 
			}
			
			switch (line[0])
			{
			case 'v':
				switch (line[1])
				{
				case ' ':
					line = parsePositionLine(fileStreamInput, line, leftHanded, &vertexDataPool, &positionDimensionCount);
					break;
				case 'n':
					line = parseNormalLine(fileStreamInput, line, leftHanded, &vertexDataPool);
					break;
				case 't':
					line = parseUVLine(fileStreamInput, line, &vertexDataPool);
					break;
				default:
					fileStreamInput.getLine(line);
					LogEX("Found a line that cannot be parsed: \"%s\"", line.c_str());
					break;
				}
				break;
			case 'f':
				vertexFormat = loadVertexFormat(line, loadFaceVertexCount(line));
				if (shouldInitialize)
				{
					initializationForFaceLineParsing(vertexFormat, positionDimensionCount, &vertices, &triangles, &indices, &baseIndex, &vertexCount, &triangleCount, &vertexByteSize, &parseFaceLine);
					shouldInitialize = false;
				}
				line = parseFaceLine(fileStreamInput, line, vertexFormat, positionDimensionCount, leftHanded, vertexDataPool, baseIndex, &indices, &vertexCount, &triangleCount, &minXYZRef, &maxXYZ);
				break;
			case 'o':
				line = parseObjectLine(fileStreamInput, line, &groupName);
				break;
			case 'g':
				line = parseGroupLine(fileStreamInput, line, &groupName);
				break;
			case 'm':
				line = parseMaterialLibLine(fileStreamInput, line, &materialDict);
				break;
			case 'u':
				if (materialKey.empty() == false)
				{
					groupListRef.emplace_back(group());
					shouldInitialize = true;
				}
				line = parseUseMaterialLine(fileStreamInput, line, &materialKey);
				break;
			case 's':
				line = parseSmoothingGroupLine(fileStreamInput, line);
				break;
			case '#':
				fileStreamInput.getLine(line);
				break;
			default:
				LogEX("Found a line that cannot be parsed: \"%s\"", line.c_str());
				break;
			}
		}

		sizeRef = maxXYZ - minXYZRef;
		groupListRef.emplace_back(group());

		



		fileStreamInput.close();

		
		


		return model;
	}
	void WavefrontOBJModelLoader::loadAsync(const std::string& filename, std::function<void(std::shared_ptr<WavefrontOBJModel>model)> processingAfterLoading, bool leftHanded)
	{
		std::thread loadingThread([=]()
		{
			const auto model = load(filename, leftHanded);
			processingAfterLoading(model);
		});	
		loadingThread.detach();
	}
}
