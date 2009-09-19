#pragma once

#include <string>
#include "regex.h"
#include "stream.h"

namespace YAML
{
	enum CHOMP { STRIP = -1, CLIP, KEEP };
	enum ACTION { NONE, BREAK, THROW };

	struct ScanScalarParams {
		ScanScalarParams(): eatEnd(false), indent(0), detectIndent(false), eatLeadingWhitespace(0), escape(0), fold(false),
			trimTrailingSpaces(0), chomp(CLIP), onDocIndicator(NONE), onTabInIndentation(NONE), leadingSpaces(false) {}

		// input:
		RegEx end;                      // what condition ends this scalar?
		bool eatEnd;                    // should we eat that condition when we see it?
		int indent;                     // what level of indentation should be eaten and ignored?
		bool detectIndent;              // should we try to autodetect the indent?
		bool eatLeadingWhitespace;      // should we continue eating this delicious indentation after 'indent' spaces?
		char escape;                    // what character do we escape on (i.e., slash or single quote) (0 for none)
		bool fold;                      // do we fold line ends?
		bool trimTrailingSpaces;        // do we remove all trailing spaces (at the very end)
		CHOMP chomp;                    // do we strip, clip, or keep trailing newlines (at the very end)
		                                //   Note: strip means kill all, clip means keep at most one, keep means keep all
		ACTION onDocIndicator;          // what do we do if we see a document indicator?
		ACTION onTabInIndentation;      // what do we do if we see a tab where we should be seeing indentation spaces

		// output:
		bool leadingSpaces;
	};

	std::string ScanScalar(Stream& INPUT, ScanScalarParams& info);
}
