#pragma once

#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GMatrix3D.h"
#include "RE/G/GMemory.h"
#include "RE/G/GNewOverrideBase.h"
#include "RE/G/GStats.h"
#include "RE/G/GString.h"

namespace RE
{
	class GFxMovieRoot;

	namespace GFxValueImpl
	{
		template <class>
		struct _is_integer :
			std::false_type
		{};

		template <>
		struct _is_integer<unsigned char> :
			std::true_type
		{};

		template <>
		struct _is_integer<char> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed char> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned short> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed short> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned int> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed int> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned long> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed long> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned long long> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed long long> :
			std::true_type
		{};

		template <class T>
		struct is_integer :
			std::conditional_t<
				std::is_enum_v<T>,
				std::true_type,
				_is_integer<
					std::remove_cv_t<T>>>
		{};

		template <class T>
		inline constexpr bool is_integer_v = is_integer<T>::value;
	}

	class GFxValue
	{
	private:
		friend class GFxMovieRoot;

	public:
		enum class ValueType
		{
			kUndefined = 0x00,
			kNull = 0x01,
			kBoolean = 0x02,
			kNumber = 0x03,
			kString = 0x04,
			kStringW = 0x05,
			kObject = 0x06,
			kArray = 0x07,
			kDisplayObject = 0x08,

			kManagedBit = 1 << 6,
			kConvertBit = 1 << 7,
			kValueMask = 0x0F,
			kTypeMask = kConvertBit | kValueMask,

			kConvertBoolean = kConvertBit | kBoolean,
			kConvertNumber = kConvertBit | kNumber,
			kConvertString = kConvertBit | kString,
			kConvertStringW = kConvertBit | kStringW
		};

		// DisplayInfo is a structure to modify display properties of a display object (MovieClips, TextField, Button). This structure is used in conjunction with GetDisplayInfo/SetDisplayInfo.
		class DisplayInfo
		{
		public:
			// Flags set to define the display properties of display objects.
			enum class Flag
			{
				kNone = 0,
				kX = 1 << 0,
				kY = 1 << 1,
				kRotation = 1 << 2,
				kXScale = 1 << 3,
				kYScale = 1 << 4,
				kAlpha = 1 << 5,
				kVisible = 1 << 6,
				kZ = 1 << 7,
				kXRotation = 1 << 8,
				kYRotation = 1 << 9,
				kZScale = 1 << 10,
				kFOV = 1 << 11,
				kPerspMatrix3D = 1 << 12,
				kViewMatrix3D = 1 << 13
			};

			DisplayInfo();                        // Initializes the DisplayInfo structure.
			DisplayInfo(double a_x, double a_y);  // Initializes the DisplayInfo structure.
			DisplayInfo(double a_rotation);       // Initializes the DisplayInfo structure.
			DisplayInfo(bool a_visible);          // Initializes the DisplayInfo structure.

			void             Clear();                                                                                                                                                                                                                                                                          // Clears all properties from the DisplayInfo object.
			[[nodiscard]] double           GetAlpha() const;                                                                                                                                                                                                                                                                 // Retrieves the alpha transparency of the display object.
			[[nodiscard]] double           GetFOV() const;                                                                                                                                                                                                                                                                   // Retrieves the perspective Field of View angle on the object.
			[[nodiscard]] double           GetRotation() const;                                                                                                                                                                                                                                                              // Retrieves the rotation of the display object.
			[[nodiscard]] bool             GetVisible() const;                                                                                                                                                                                                                                                               // Retrieves the Boolean value to indicate the visibility of the display object.
			[[nodiscard]] const GMatrix3D* GetPerspectiveMatrix3D() const;                                                                                                                                                                                                                                                   // Returns a temporary pointer to the 3D perspective matrix set on a 3D movie clip.
			[[nodiscard]] const GMatrix3D* GetViewMatrix3D() const;                                                                                                                                                                                                                                                          // Returns a temporary pointer to the 3D view matrix set on the 3D movie clip.
			[[nodiscard]] double           GetX() const;                                                                                                                                                                                                                                                                     // Retrieves the x coordinate of the display object relative to the parent movie clip.
			[[nodiscard]] double           GetY() const;                                                                                                                                                                                                                                                                     // Retrieves the y coordinate of the display object relative to the parent movie clip.
			[[nodiscard]] double           GetZ() const;                                                                                                                                                                                                                                                                     // Retrieves the z coordinate of the display object relative to the parent movie clip.
			[[nodiscard]] double           GetXRotation() const;                                                                                                                                                                                                                                                             // Returns the rotation of the object around the X axis.
			[[nodiscard]] double           GetYRotation() const;                                                                                                                                                                                                                                                             // Returns the rotation of the object around the Y axis.
			[[nodiscard]] double           GetXScale() const;                                                                                                                                                                                                                                                                // Retrieves the horizontal scale of the display object.
			[[nodiscard]] double           GetYScale() const;                                                                                                                                                                                                                                                                // Retrieves the vertical scale of the display object.
			[[nodiscard]] double           GetZScale() const;                                                                                                                                                                                                                                                                // Retrieves the scale of the object along the Z axis.
			[[nodiscard]] bool             IsFlagSet(Flag a_flag) const;                                                                                                                                                                                                                                                     // Determines if a property of the DisplayInfo object is set
			void             Initialize(Flag a_varsSet, double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale, double a_fov, const GMatrix3D* a_viewM, const GMatrix3D* a_perspM);  // Initializes the display properties of a display object.
			void             SetVisible(bool a_visible);                                                                                                                                                                                                                                                       // Sets the visibility of the display object.
			void             SetPerspectiveMatrix3D(const GMatrix3D* a_mat);                                                                                                                                                                                                                                   // Sets the erspective matrix for a 3D movie clip.
			void             Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible);                                                                                                                                                                 // Sets the values in Flag structure indicating the display properties of objects on stage.
			void             Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale);                                                                                            // Sets the values in Flags structure indicating the display properties of objects on stage.
			void             SetViewMatrix3D(const GMatrix3D* a_mat);                                                                                                                                                                                                                                          // Sets the view matrix for a 3D movie clip.
			void             SetAlpha(double a_alpha);                                                                                                                                                                                                                                                         // Sets the alpha transparency of the display object.
			void             SetFOV(double a_fov);                                                                                                                                                                                                                                                             // Sets the perspective Field of View angle in degrees.
			void             SetPosition(double a_x, double a_y);                                                                                                                                                                                                                                              // Sets the coordinate position of the display object.
			void             SetRotation(double a_degrees);                                                                                                                                                                                                                                                    // Sets the rotation of the display object.
			void             SetScale(double a_xScale, double a_yScale);                                                                                                                                                                                                                                       // Sets the scaling factor of the display object.
			void             SetX(double a_x);                                                                                                                                                                                                                                                                 // Sets the x coordinate of the display object relative to the parent movie clip.
			void             SetXRotation(double a_degrees);                                                                                                                                                                                                                                                   // Sets the rotation of the object around the X axis.
			void             SetXScale(double a_xScale);                                                                                                                                                                                                                                                       // Sets the horizontal scale of the display object.
			void             SetY(double a_y);                                                                                                                                                                                                                                                                 // Sets the y coordinate of the display object relative to the parent movie clip.
			void             SetYRotation(double a_degrees);                                                                                                                                                                                                                                                   // Sets the rotation of the object around the Y axis.
			void             SetYScale(double a_yScale);                                                                                                                                                                                                                                                       // Sets the vertical scale of the display object.
			void             SetZ(double a_z);                                                                                                                                                                                                                                                                 // Sets the z coordinate of the display object relative to the parent movie clip.
			void             SetZScale(double a_zScale);                                                                                                                                                                                                                                                       // Sets the scale of the object along the Z axis

		protected:
			void SetFlags(Flag a_flags);
			void ClearFlags(Flag a_flags);

			// members
			double                                _x;              // 00
			double                                _y;              // 08
			double                                _rotation;       // 10
			double                                _xScale;         // 18
			double                                _yScale;         // 20
			double                                _alpha;          // 28
			bool                                  _visible;        // 30
			std::uint8_t                          _pad31;          // 31
			std::uint16_t                         _pad32;          // 32
			std::uint32_t                         _pad34;          // 34
			double                                _z;              // 38
			double                                _xRotation;      // 40
			double                                _yRotation;      // 48
			double                                _zScale;         // 50
			double                                _fov;            // 58
			GMatrix3D                             _viewMatrix3D;   // 60
			GMatrix3D                             _perspMatrix3D;  // A0
			stl::enumeration<Flag, std::uint16_t> _flags;          // E0
			std::uint16_t                         _padD2;          // E2
			std::uint32_t                         _padD4;          // E4
		};
		static_assert(sizeof(DisplayInfo) == 0xE8);

		class ObjectInterface : public GNewOverrideBase<GFxStatMovieViews::kGFxStatMV_Other_Mem>
		{
		public:
			class ObjVisitor
			{
			public:
				virtual ~ObjVisitor();  // 00

				// add
				virtual void Visit(const char* a_name, const GFxValue& a_val) = 0;  // 01
			};

			class ArrVisitor
			{
			public:
				virtual ~ArrVisitor();  // 00

				// add
				virtual void Visit(std::uint32_t a_idx, const GFxValue& a_val) = 0;  // 01
			};

			ObjectInterface(GFxMovieRoot* a_movieRoot);

			void ObjectAddRef(GFxValue* a_val, void* a_obj);
			void ObjectRelease(GFxValue* a_val, void* a_obj);

			bool HasMember(void* a_data, const char* a_name, bool a_isDObj) const;
			bool GetMember(void* a_data, const char* a_name, GFxValue* a_val, bool a_isDObj) const;
			bool SetMember(void* a_data, const char* a_name, const GFxValue& a_value, bool a_isDObj);
			bool Invoke(void* a_data, GFxValue* a_result, const char* a_name, const GFxValue* a_args, UPInt a_numArgs, bool a_isDObj);
			bool DeleteMember(void* a_data, const char* a_name, bool a_isDObj);

			std::uint32_t GetArraySize(void* a_data) const;
			bool          SetArraySize(void* a_data, std::uint32_t a_size);
			bool          GetElement(void* a_data, std::uint32_t a_idx, GFxValue* a_val) const;
			bool          SetElement(void* a_data, std::uint32_t a_idx, const GFxValue& a_val);
			bool          PushBack(void* a_data, const GFxValue& a_value);
			bool          RemoveElements(void* a_data, std::uint32_t a_idx, std::int32_t a_count);

			bool GetDisplayInfo(void* a_data, DisplayInfo* a_info) const;
			bool SetDisplayInfo(void* a_data, const DisplayInfo& a_info);

			bool SetText(void* a_data, const char* a_text, bool a_isHTML);

			bool AttachMovie(void* a_data, GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth, const GFxValue* a_initObj);
			bool GotoAndPlay(void* a_data, const char* a_frame, bool a_stop);

			bool IsSameContext(const ObjectInterface* a_rhs) const;

		protected:
			// members
			GFxMovieRoot* _movieRoot;  // 0
		};
		static_assert(sizeof(ObjectInterface) == 0x8);

		using ObjectVisitor = ObjectInterface::ObjVisitor;
		using ArrayVisitor = ObjectInterface::ArrVisitor;

		GFxValue();
		GFxValue(ValueType a_rhs);
		GFxValue(std::nullptr_t);
		GFxValue(double a_rhs);
		GFxValue(bool a_rhs);
		GFxValue(const char* a_rhs);
		GFxValue(std::string_view a_rhs);
		GFxValue(const wchar_t* a_rhs);
		GFxValue(std::wstring_view a_rhs);
		GFxValue(const GFxValue& a_rhs);
		GFxValue(GFxValue&& a_rhs);

		template <
			class T,
			std::enable_if_t<
				GFxValueImpl::is_integer_v<T>,
				int> = 0>
		inline GFxValue(T a_val) :
			GFxValue(static_cast<double>(a_val))
		{}

		~GFxValue();

		GFxValue& operator=(std::nullptr_t);
		GFxValue& operator=(double a_rhs);
		GFxValue& operator=(bool a_rhs);
		GFxValue& operator=(const char* a_rhs);
		GFxValue& operator=(std::string_view a_rhs);
		GFxValue& operator=(const wchar_t* a_rhs);
		GFxValue& operator=(std::wstring_view a_rhs);
		GFxValue& operator=(const GFxValue& a_rhs);
		GFxValue& operator=(GFxValue&& a_rhs);

		template <
			class T,
			std::enable_if_t<
				GFxValueImpl::is_integer_v<T>,
				int> = 0>
		inline GFxValue& operator=(T a_val)
		{
			return *this = static_cast<double>(a_val);
		}

		bool operator==(const GFxValue& a_rhs) const;

		[[nodiscard]] GString ToString() const;

		[[nodiscard]] ValueType      GetType() const;
		[[nodiscard]] bool           IsUndefined() const;
		[[nodiscard]] bool           IsNull() const;
		[[nodiscard]] bool           IsBool() const;
		[[nodiscard]] bool           IsNumber() const;
		[[nodiscard]] bool           IsString() const;
		[[nodiscard]] bool           IsStringW() const;
		[[nodiscard]] bool           IsObject() const;
		[[nodiscard]] bool           IsArray() const;
		[[nodiscard]] bool           IsDisplayObject() const;
		[[nodiscard]] bool           GetBool() const;
		[[nodiscard]] double         GetNumber() const;
		[[nodiscard]] std::ptrdiff_t GetSInt() const;
		[[nodiscard]] std::size_t    GetUInt() const;
		[[nodiscard]] const char*    GetString() const;
		[[nodiscard]] const wchar_t* GetStringW() const;

		void SetUndefined();
		void SetNull();
		void SetBoolean(bool a_val);
		void SetNumber(double a_val);
		void SetString(const char* a_str);
		void SetString(std::string_view a_str);
		void SetStringW(const wchar_t* a_str);
		void SetStringW(std::wstring_view a_str);

		void SetConvertBoolean();
		void SetConvertNumber();
		void SetConvertString();
		void SetConvertStringW();

		// AS Object support. Valid for Object, Array and DisplayObject types
		bool HasMember(const char* a_name) const;
		bool GetMember(const char* a_name, GFxValue* a_val) const;
		bool SetMember(const char* a_name, const GFxValue& a_val);
		bool Invoke(const char* a_name, GFxValue* a_result, const GFxValue* a_args, UPInt a_numArgs);
		bool Invoke(const char* a_name, GFxValue* a_result = nullptr);
		bool DeleteMember(const char* a_name);

		template <std::size_t N>
		inline bool Invoke(const char* a_name, const std::array<GFxValue, N>& a_args)
		{
			return Invoke(a_name, nullptr, a_args);
		}

		template <std::size_t N>
		inline bool Invoke(const char* a_name, GFxValue* a_result, const std::array<GFxValue, N>& a_args)
		{
			return Invoke(a_name, a_result, a_args.data(), a_args.size());
		}

		// AS Array support. Valid for Array type
		[[nodiscard]] std::uint32_t GetArraySize() const;
		bool          SetArraySize(std::uint32_t a_size);
		bool          GetElement(std::uint32_t a_idx, GFxValue* a_val) const;
		bool          SetElement(std::uint32_t a_idx, const GFxValue& a_val);
		bool          PushBack(const GFxValue& a_val);
		bool          RemoveElements(std::uint32_t a_idx, std::int32_t a_count = -1);
		bool          RemoveElement(std::uint32_t a_idx);
		bool          ClearElements();

		// AS MovieClips, Buttons, TextFields support. Valid for DisplayObject type
		bool GetDisplayInfo(DisplayInfo* a_info) const;
		bool SetDisplayInfo(const DisplayInfo& a_info);

		// AS TextField support. Valid for DisplayObject type.
		bool SetText(const char* a_text);
		bool SetTextHTML(const char* a_html);

		// AS MovieClip support. Valid for MovieClips.
		bool AttachMovie(GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, std::int32_t a_depth = -1, const GFxValue* a_initObj = nullptr);
		bool GotoAndPlay(const char* a_frame);
		bool GotoAndStop(const char* a_frame);

		GFC_MEMORY_REDEFINE_NEW(GFxValue, GStatGroups::kGStatGroup_Default);

	protected:
		[[nodiscard]] bool IsManagedValue() const;
		void AcquireManagedValue(const GFxValue& a_rhs);
		void ReleaseManagedValue();
		void ChangeType(ValueType a_type);

		union ValueUnion
		{
			constexpr ValueUnion() :
				obj(nullptr)
			{}

			double          number;
			bool            boolean;
			const char*     string;
			const char**    managedString;
			const wchar_t*  wideString;
			const wchar_t** managedWideString;
			void*           obj;
		};
		static_assert(sizeof(ValueUnion) == 0x8);

		// members
		ObjectInterface*                           _objectInterface;  // 00
		stl::enumeration<ValueType, std::uint32_t> _type;             // 08
		std::uint32_t                              _pad0C;            // 0C
		ValueUnion                                 _value;            // 10
	};
	static_assert(sizeof(GFxValue) == 0x18);
}
