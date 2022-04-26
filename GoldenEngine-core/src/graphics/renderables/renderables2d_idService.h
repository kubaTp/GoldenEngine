#pragma once
#include <vector>
#include <stdint.h>
#include <cstdlib>

namespace golden { namespace graphics {

	struct RenderablesIDService
	{
		static std::vector<uint64_t> IDs;
		static uint64_t maxId;
		static const uint64_t& genNewID()
		{
			uint32_t generatedId = rand() % (maxId + 1);		

			while (validateIds(generatedId))
			{
				generatedId = rand() % (maxId + 1);
			}

			IDs.push_back(generatedId);

			return generatedId;
		}

	private:
		static bool validateIds(const uint64_t& newid)
		{
			for (const uint64_t& id : IDs)
			{
				if (newid == id)
				{
					return true;
				}
			}

			return false;
		}
		
	private:
		RenderablesIDService();
	};
}}