/*******************************************************************************
* Copyright 2016-2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef MKLDNN_H
#define MKLDNN_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* All symbols shall be internal unless marked as MKLDNN_API */
#if defined _WIN32 || defined __CYGWIN__
#   define MKLDNN_HELPER_DLL_IMPORT __declspec(dllimport)
#   define MKLDNN_HELPER_DLL_EXPORT __declspec(dllexport)
#else
#   if __GNUC__ >= 4
#       define MKLDNN_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#       define MKLDNN_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#   else
#       define MKLDNN_HELPER_DLL_IMPORT
#       define MKLDNN_HELPER_DLL_EXPORT
#   endif
#endif

#ifdef MKLDNN_DLL
#   ifdef MKLDNN_DLL_EXPORTS
#       define MKLDNN_API MKLDNN_HELPER_DLL_EXPORT
#   else
#       define MKLDNN_API MKLDNN_HELPER_DLL_IMPORT
#   endif
#else
#   define MKLDNN_API
#endif

#if defined (__GNUC__)
#   define MKLDNN_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#   define MKLDNN_DEPRECATED __declspec(deprecated)
#else
#   define MKLDNN_DEPRECATED
#endif

#include "mkldnn_types.h"
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup c_api C API
 * @{ */

/** @addtogroup c_api_primitive Primitive operations
 * @{ */

/** @addtogroup c_api_primitive_common Common primitive operations
 * @{ */

/** Creates a primitive descriptor @p iterator for given @p op_desc, @p engine,
 * and optionally a hint primitive descriptor from forward propagation
 * (required for backward propagation). Pass @c NULL for forward propagation.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_iterator_create(
        mkldnn_primitive_desc_iterator_t *iterator,
        const_mkldnn_op_desc_t op_desc, mkldnn_engine_t engine,
        const_mkldnn_primitive_desc_t hint_forward_primitive_desc);

/** Creates a primitive descriptor @p iterator for given @p op_desc, @p attr,
 * @p engine, and optionally a hint primitive descriptor from forward
 * propagation (required for backward propagation). Pass @c NULL for forward
 * propagation.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_iterator_create_v2(
        mkldnn_primitive_desc_iterator_t *iterator,
        const_mkldnn_op_desc_t op_desc, const_mkldnn_primitive_attr_t attr,
        mkldnn_engine_t engine,
        const_mkldnn_primitive_desc_t hint_forward_primitive_desc);

/** Iterates over primitive descriptors. Returns #mkldnn_iterator_ends if no
 * more primitive descriptors are available */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_iterator_next(
        mkldnn_primitive_desc_iterator_t iterator);

/** Fetches current primitive descriptor.
 *
 * @note
 *     fetched primitive descriptor should be deleted by user using
 *     mkldnn_primitive_desc_destroy() once becomes unneeded */
mkldnn_primitive_desc_t MKLDNN_API mkldnn_primitive_desc_iterator_fetch(
        const_mkldnn_primitive_desc_iterator_t iterator);

/** Deletes a primitive descriptor @p iterator */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_iterator_destroy(
        mkldnn_primitive_desc_iterator_t iterator);

/** Creates a @p primitive_desc using @p op_desc, @p engine, and optionally a
 * hint primitive descriptor from forward propagation. The call is equivalent
 * to create a primitive descriptor iterator, instantly fetch a primitive_desc
 * and destroy the iterator. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_create(
        mkldnn_primitive_desc_t *primitive_desc,
        const_mkldnn_op_desc_t op_desc, mkldnn_engine_t engine,
        const_mkldnn_primitive_desc_t hint_forward_primitive_desc);

/** Creates a @p primitive_desc using @p op_desc, @p attr, @p engine, and
 * optionally a hint primitive descriptor from forward propagation. The call is
 * equivalent to create a primitive descriptor iterator, instantly fetch a @p
 * primitive_desc and destroy the iterator. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_create_v2(
        mkldnn_primitive_desc_t *primitive_desc,
        const_mkldnn_op_desc_t op_desc, const_mkldnn_primitive_attr_t attr,
        mkldnn_engine_t engine,
        const_mkldnn_primitive_desc_t hint_forward_primitive_desc);

/** Makes a copy of a @p primitive_desc. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_clone(
        mkldnn_primitive_desc_t *primitive_desc,
        const_mkldnn_primitive_desc_t existing_primitive_desc);

/** Returns a constant reference to the attribute of a @p primitive_desc.
 *
 * @warning
 *      User should not destroy obtained @p attr
 *
 * @warning
 *      The lifetime of an @p attr is same as @p primitive_desc, so it is
 *      illegal to use the @p attr once @p primitive_desc is destroyed */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_get_attr(
        const_mkldnn_primitive_desc_t primitive_desc,
        const_mkldnn_primitive_attr_t *attr);

/** Deletes a @p primitive_desc. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_destroy(
        mkldnn_primitive_desc_t primitive_desc);

/** Queries primitive descriptor
 *
 * @sa mkldnn_query_t */
mkldnn_status_t MKLDNN_API mkldnn_primitive_desc_query(
        const_mkldnn_primitive_desc_t primitive_desc, mkldnn_query_t what,
        int index, void *result);

/** Queries primitive descriptor for memory descriptor
 *
 * @returns NULL in case of any error */
const mkldnn_memory_desc_t MKLDNN_API *mkldnn_primitive_desc_query_memory_d(
        const_mkldnn_primitive_desc_t primitive_desc);

/** Queries primitive descriptor for primitive descriptor
 *
 * @returns NULL in case of any error */
const_mkldnn_primitive_desc_t MKLDNN_API mkldnn_primitive_desc_query_pd(
        const_mkldnn_primitive_desc_t primitive_desc, mkldnn_query_t what,
        int index);

/** Queries primitive descriptor for signed 32bit int
 *
 * @returns 0 in case of any error */
int MKLDNN_API mkldnn_primitive_desc_query_s32(
        const_mkldnn_primitive_desc_t primitive_desc, mkldnn_query_t what,
        int index);

/** Creates a @p primitive using a @p primitive_desc descriptor and arrays of
 * @p inputs and @p outputs. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_create(
        mkldnn_primitive_t *primitive,
        const_mkldnn_primitive_desc_t primitive_desc,
        const mkldnn_primitive_at_t *inputs,
        const_mkldnn_primitive_t *outputs);

/** Retrieves a reference to the @p primitive_desc descriptor of given @p
 * primitive.
 *
 * @warning
 *     Returned object must not be destroyed by user. 'const' qualifier of the
 *     returned object prevents such attempts. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_get_primitive_desc(
        const_mkldnn_primitive_t primitive,
        const_mkldnn_primitive_desc_t *primitive_desc);

/** For a @p primitive, returns @p input at the @p index position. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_get_input_at(
        const_mkldnn_primitive_t primitive, size_t index,
        mkldnn_primitive_at_t *input);

/** For a @p primitive, returns @p output at the @p index position. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_get_output(
        const_mkldnn_primitive_t primitive, size_t index,
        const_mkldnn_primitive_t *output);

/** Deletes a @p primitive. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_destroy(
        mkldnn_primitive_t primitive);

/** Creates an #mkldnn_primitive_at_t structure from a @p primitive and @p
 * output_index. This function only fills in the data structure
 * and does not check whether parameters are correct. The actual error checking
 * is done when the resulting #mkldnn_primitive_at structure is passed to a
 * primitive creation function. */
mkldnn_primitive_at_t MKLDNN_API mkldnn_primitive_at(
        const_mkldnn_primitive_t primitive, size_t output_index);

/** @} */

/** @addtogroup c_api_attributes Attributes
 * An extension for controlling primitive behavior.
 * @{ */

/** Creates an empty (default) @p attr attribute. All the parameters set to
 * default values.
 *
 * An empty attribute is used in primitive descriptor creating whenever it is
 * not passed explicitly, e.g. in mkldnn_primitive_desc_create.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_create(
        mkldnn_primitive_attr_t *attr);

/** Makes a copy of an @p existing_attr. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_clone(
        mkldnn_primitive_attr_t *attr,
        const_mkldnn_primitive_attr_t existing_attr);

/** Deletes an @p attr. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_destroy(
        mkldnn_primitive_attr_t attr);

/** Returns integer output rounding mode @p round_mode for a given @p attr,
 * previously set by mkldnn_primitive_attr_set_int_output_round_mode. */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_get_int_output_round_mode(
        const_mkldnn_primitive_attr_t attr, mkldnn_round_mode_t *round_mode);

/** Sets output rounding mode @p round_mode for integer operations for a given
 * @p attr.
 *
 * The default value is #mkldnn_round_nearest.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_set_int_output_round_mode(
        mkldnn_primitive_attr_t attr, mkldnn_round_mode_t round_mode);

/** Returns @p count, correspondence scale @p mask, and pointer to a constant
 * floating point array of output @p scales for given @p attr, previously set
 * by mkldnn_primitive_attr_set_output_scales.
 *
 * @warning
 *      @p scales array points to the internal @p attr field, so user should
 *      not modify/destroy @p scales.
 *
 * @warning
 *      The lifetime of @p scales is same as @p attr it belongs to, so it is
 *      illegal to use the @p scales after @p attr is destroyed
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_get_output_scales(
        const_mkldnn_primitive_attr_t attr, int *count, int *mask,
        const float **scales);

/** Sets output @p scales for primitive operations. The number of elements @p
 * count and correspondence scale @p mask are stored for future use.
 *
 * The @p mask argument defines correspondence between output tensor dimensions
 * and the @p scales array. Set i-th bit of @p mask to 1 to use dedicated
 * scaling factor for each slice of the output tensor over i-th dimension. Set
 * @p mask to 0 to use common scaling factor for the whole output tensor.
 *
 * @note
 *      The dimension order is always native and does not depend on the actual
 *      layout used. Examples:
 *       - 2D dimensional data the order of dimensions is always: (n, c)
 *       - 4D dimensional data the order is always: (n, c, h, w)
 *       - 5D dimensional weights the order is always: (g, oc, ic, kh, kw)
 *
 * Example usage:
 * @code
 *      int mb = 32, oc = 32, oh = 14, ow = 14; // convolution output params
 *      float scales[oc] = { ... }; // unique output scales per output channel
 *      int oc_dim = 1; // mb_dim = 0, channel_dim = 1, height_dim = 2, ...
 *
 *      mkldnn_convolution_desc_t cd; // create & configure convolution op_desc
 *
 *      mkldnn_primitive_attr_t attr;
 *      mkldnn_primitive_attr_create(&attr);  // create default attributes
 *      mkldnn_primitive_attr_set_output_scales(attr, oc, 1 << oc_dim, scales);
 *
 *      mkldnn_primitive_desc_t cpd;
 *      mkldnn_primitive_desc_create_v2(&cpd, &cd, attr, NULL);
 * @endcode
 *
 * @note
 *      There is no way to check that @p count corresponds to @p mask until an
 *      actual primitive descriptor is created, so it is user's responsibility
 *      to set proper values. The following formula must be hold:
 *
 *      \f[count = \prod\limits_{d \in mask} output.dims[d]\f]
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_set_output_scales(
        mkldnn_primitive_attr_t attr, int count, int mask,
        const float *scales);

/** Returns @p post_ops for given attr.
 *
 * @warning
 *      @p post_ops points to the internal @p attr field, so user should not
 *      modify/destroy @p post_ops. Also the lifetime of @p post_ops is the
 *      same as @p attr it belongs to, so it is illegal to use @p post_ops once
 *      @p attr is destroyed.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_get_post_ops(
        const_mkldnn_primitive_attr_t attr, const_mkldnn_post_ops_t *post_ops);

/** Sets configured @p post_ops to an attribute @p attr for future use (when
 * primitive descriptor is being created.
 *
 * @note
 *      At this point of time there is no way to check whether primitive
 *      descriptor does or does not support given sequence of post operations.
 *      That means that user should handle an error that might happen at
 *      mkldnn_primitive_desc_create call.
 */
mkldnn_status_t MKLDNN_API mkldnn_primitive_attr_set_post_ops(
        mkldnn_primitive_attr_t attr, const_mkldnn_post_ops_t post_ops);

/** @addtogroup c_api_attributes_post_ops Sequence of post operations
 * An extension for performing extra operations after base operation.
 * @{ */

/** Creates an empty sequence of post operations @p post_ops. */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_create(mkldnn_post_ops_t *post_ops);

/** Deletes a @p post_ops sequence. */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_destroy(mkldnn_post_ops_t post_ops);

/** Returns the @p length of post operations for given @p post_ops. */
int MKLDNN_API mkldnn_post_ops_len(const_mkldnn_post_ops_t post_ops);

/** Returns the type of post operation with index @p index in given
 * @p post_ops. In case of error returns #mkldnn_undefined_primitive. */
mkldnn_primitive_kind_t MKLDNN_API mkldnn_post_ops_get_kind(
        const_mkldnn_post_ops_t post_ops, int index);

/** Appends accumulation (sum) post operation to the @p post_ops. Prior to
 * accumulating the result the previous value would be multiplied by @p scale.
 *
 * The kind of this post operation is #mkldnn_sum.
 *
 * This feature might improve performance for the cases like residual learning
 * blocks, where the result of convolution is accumulated to the previously
 * computed activations. Scale parameter @p scale might be extremely for the
 * integer-based computations, when the result and previous activations have
 * different logical scaling factors.
 *
 * In the simplest case when the accumulation is the only post operation, the
 * computations would be:
 * dst[] <- scale * dst[] + op(...) // instead of dst[] <- op(...)
 *
 * @note
 *      This post op (as well as all the others) disregards the original layout
 *      of dst, i.e. the layout of the original dst is expected to be the same
 *      as the layout of stored dst.
 */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_append_sum(
        mkldnn_post_ops_t post_ops, float scale);

/** Gets the parameters of the accumulation (sum) post operation with index
 * @p index in the sequence of @p post_ops.
 *
 * @note
 *      If index @p index would not correspond to the accumulation post
 *      operation, the function return #mkldnn_invalid_arguments.
 */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_get_params_sum(
        const_mkldnn_post_ops_t post_ops, int index, float *scale);

/** Appends eltwise post operation to the @p post_ops with given parameters
 * @p kind, @p alpha and @p beta (@sa mkldnn_eltwise_forward_desc_init and
 * mkldnn_eltwise_desc_t).
 *
 * The kind of this post operation is #mkldnn_eltwise.
 *
 * In the simplest case when the eltwise is the only post operation, the
 * computations would be:
 * dst[] <- scale * eltwise_op ( op(...) ) // instead of dst[] <- op(...)
 * where eltwise_op is configured with given parameters.
 */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_append_eltwise(
        mkldnn_post_ops_t post_ops, float scale, mkldnn_alg_kind_t alg,
        float alpha, float beta);

/** Gets the eltwise parameters of the post operation with index @p index in
 * the sequence of @p post_ops.
 */
mkldnn_status_t MKLDNN_API mkldnn_post_ops_get_params_eltwise(
        const_mkldnn_post_ops_t post_ops, int index, float *scale,
        mkldnn_alg_kind_t *alg, float *alpha, float *beta);

/** @} */

/** @} */

/** @addtogroup c_api_memory Memory
 * A primitive to describe data.
 * @{ */

/** Initializes a @p memory_desc memory descriptor using @p ndims, @p dims, @p
 * data_type, and data @p format. @p format can be #mkldnn_any, which means
 * that specific data layouts are not permitted. */
mkldnn_status_t MKLDNN_API mkldnn_memory_desc_init(
        mkldnn_memory_desc_t *memory_desc, int ndims, const mkldnn_dims_t dims,
        mkldnn_data_type_t data_type, mkldnn_memory_format_t format);

/** Creates a @p memory_primitive_desc memory primitive descriptor using @p
 * memory_desc and @p engine. @p memory_desc cannot be uncertain, that is,
 * initialized with #mkldnn_any. */
mkldnn_status_t MKLDNN_API mkldnn_memory_primitive_desc_create(
        mkldnn_primitive_desc_t *memory_primitive_desc,
        const mkldnn_memory_desc_t *memory_desc, mkldnn_engine_t engine);

/** Creates a @p view_primitive_desc for a given @p memory_primitive_desc, with
 * @p dims sizes and @p offset offsets. May fail if layout used does not allow
 * obtain desired view. In this case consider using extract primitive */
mkldnn_status_t MKLDNN_API mkldnn_view_primitive_desc_create(
        mkldnn_primitive_desc_t *view_primitive_desc,
        const_mkldnn_primitive_desc_t memory_primitive_desc,
        const mkldnn_dims_t dims, const mkldnn_dims_t offsets);

/** Compares two descriptors of memory primitives.
 * @return 1 if the descriptors are the same.
 * @return 0 if the descriptors are different.
 *
 * Use this function to identify whether a reorder is required for the memory
 * primitives. @p lhs and @p rhs must be either memory or view primitive
 * descriptors. */
int MKLDNN_API mkldnn_memory_primitive_desc_equal(
        const_mkldnn_primitive_desc_t lhs,
        const_mkldnn_primitive_desc_t rhs);

/** Returns the size (in bytes) that is required for given @p
 * memory_primitive_desc */
/* XXX: view? */
size_t MKLDNN_API mkldnn_memory_primitive_desc_get_size(
        const_mkldnn_primitive_desc_t memory_primitive_desc);

/** For a @p memory primitive, returns the data @p handle. For the CPU engine,
 * the data handle is a pointer to the actual data. */
/* XXX: view? */
mkldnn_status_t MKLDNN_API mkldnn_memory_get_data_handle(
        const_mkldnn_primitive_t memory, void **handle);

/** For a @p memory primitive, sets the data @p handle. */
mkldnn_status_t MKLDNN_API mkldnn_memory_set_data_handle(
        mkldnn_primitive_t memory, void *handle);

/** @} */

/** @addtogroup c_api_reorder Reorder
 * A primitive to copy data between memory formats.
 * @{ */

/** Initializes a @p reorder_primitive_desc using descriptors of @p input and
 * @p output memory primitives. */
mkldnn_status_t MKLDNN_API mkldnn_reorder_primitive_desc_create(
        mkldnn_primitive_desc_t *reorder_primitive_desc,
        const_mkldnn_primitive_desc_t input,
        const_mkldnn_primitive_desc_t output);

/** Initializes a @p reorder_primitive_desc using an @p attr attribute and
 * descriptors of @p input and @p output memory primitives. */
mkldnn_status_t MKLDNN_API mkldnn_reorder_primitive_desc_create_v2(
        mkldnn_primitive_desc_t *reorder_primitive_desc,
        const_mkldnn_primitive_desc_t input,
        const_mkldnn_primitive_desc_t output,
        const_mkldnn_primitive_attr_t attr);

/** @} */

/** @addtogroup c_api_concat Concat
 * A primitive to concatenate data by arbitrary dimension
 * @{ */

/** Creates out-of-place @p concat_primitive_desc for concatenation of @p n
 * inputs by @p concat_dimension with resulting @p output_desc memory
 * descriptor. @p output_desc can be NULL or be specified with #mkldnn_any
 * format -- in this case appropriate memory format would be chosen
 * automatically. */
mkldnn_status_t MKLDNN_API mkldnn_concat_primitive_desc_create(
        mkldnn_primitive_desc_t *concat_primitive_desc,
        const mkldnn_memory_desc_t *output_desc, int n, int concat_dimension,
        const_mkldnn_primitive_desc_t *input_pds);

#if 0
/** Creates in-place @p concat_primitive_desc for given @p n @p inputs memory
 * primitive descriptors along @p concat_dimension. All inputs must have the
 * same memory format. Output memory format would be the same. Likewise
 * view_primitive_desc_create the call may fail, if memory format of inputs do
 * not allow inplace concatenation for given sizes.
 *
 * @note this primitive is more like a synchronization stub for concatenation,
 * since concat_inplace does no operation during execution.
 *
 * @note since not operation happens user must ensure that input */
mkldnn_status_t MKLDNN_API mkldnn_concat_inplace_by_input_primitive_desc_create(
        mkldnn_primitive_desc_t *concat_primitive_desc,
        int n, int concat_dimension, const_mkldnn_primitive_desc_t *inputs);

/** Creates in-place @p concat_primitive_desc for given @p output memory
 * descriptor and @n inputs with @p sizes sizes along @p concat_dimension. As
 * opposed to out-of-place concatenation @p output must be fully defined here.
 * Likewise view_primitive_desc_create the call may fail, because given memory
 * format does not allow inplace concatenation for given sizes.
 *
 * @note this primitive is more like a synchronization stub for concatenation,
 * since concat_inplace does no operation during execution. */
mkldnn_status_t MKLDNN_API mkldnn_concat_inplace_by_output_primitive_desc_create(
        mkldnn_primitive_desc_t *concat_primitive_desc,
        const mkldnn_primitive_desc_t output, int n, int concat_dimension,
        int *sizes);
#endif

/** @} */

/** @addtogroup c_api_sum Sum
 * A primitive to sum data
 * @{ */

/** Creates out-of-place @p sum_primitive_desc for sum of @p n
 * inputs multiplied by scale with resulting @p output_desc memory
 * descriptor. @p output_desc can be NULL or be specified with #mkldnn_any
 * format -- in this case appropriate memory format would be chosen
 * automatically. */
mkldnn_status_t MKLDNN_API mkldnn_sum_primitive_desc_create(
        mkldnn_primitive_desc_t *sum_primitive_desc,
        const mkldnn_memory_desc_t *output_desc, int n, const float *scales,
        const_mkldnn_primitive_desc_t *input_pds);

/** @} */

/** @addtogroup c_api_convolution Convolution
 * A primitive to compute convolution using different algorithms.
 *
 * \f[dst[n][oc][oh][ow]  =
 *     \sum_{kw=0}^{KW}\sum_{kh=0}^{KH}\sum_{ic=0}^{IC}
 *     src[n][ic][oh \cdot s_h - p_l[0] + kh][ow \cdot s_w - p_r[1] + kw]
 *     \cdot weights[g][oc][ic][kh][kw]
 *     + bias[g][oc],\f]
 *
 * where size of output spatial domain is given by
 * \f$ OH = \left\lfloor{\frac{IH - KH + p_l[0] + p_r[0]}{s_h}}
 *          \right\rfloor + 1\f$,
 * \f$ OW = \left\lfloor{\frac{IW - KW + p_l[1] + p_r[1]}{s_w}}
 *          \right\rfloor + 1\f$,
 *
 * and summation is carried over input channels \f$ic\f$ in
 * group \f$g\f$, and \f$s_h, s_w\f$ are @p strides and
 * \f$p_l, p_r\f$ are @p padding_l and @p padding_r.
 * @{ */

/** Initializes a convolution descriptor @p conv_desc for forward propagation
 * using @p prop_kind (possible values are #mkldnn_forward_training or
 * #mkldnn_forward_inference), @p alg_kind, memory descriptors, @p strides, @p
 * padding_l, @p padding_r, and @p padding_kind. In order to create a
 * convolution without bias, @p bias_desc should be either @c NULL or point to
 * a descriptor with memory format equals to #mkldnn_format_undef.
 *
 * @note if @p padding_r is @c NULL, the padding is supposed to be symmetric
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_convolution_forward_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);

/** Initializes a dilated convolution descriptor @p conv_desc for forward
 * propagation using @p prop_kind (possible values are #mkldnn_forward_training
 * or #mkldnn_forward_inference), @p alg_kind, memory descriptors, @p strides,
 * @p dilates, @p padding_l, @p padding_r, and @p padding_kind.
 * In order to create a dilated convolution without bias, @p bias_desc
 * should be either @c NULL or point to a descriptor with memory format equals
 * to #mkldnn_format_undef.
 *
 * @note if @p padding_r is @c NULL, the padding is supposed to be symmetric
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_dilated_convolution_forward_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t dilates, const mkldnn_dims_t padding_l,
        const mkldnn_dims_t padding_r, mkldnn_padding_kind_t padding_kind);

/** Initializes a convolution descriptor @p conv_desc for backward propagation
 * with respect to data using @p alg_kind, memory descriptors, @p strides, @p
 * padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_convolution_backward_data_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);

/** Initializes a dilated convolution descriptor @p conv_desc for backward
 * propagation with respect to data using @p alg_kind, memory descriptors, @p
 * strides, @p dilates @p padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_dilated_convolution_backward_data_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t dilates, const mkldnn_dims_t padding_l,
        const mkldnn_dims_t padding_r, mkldnn_padding_kind_t padding_kind);

/** Initializes a convolution descriptor @p conv_desc for backward propagation
 * with respect to weights using @p alg_kind, memory descriptors, @p strides,
 * @p padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_convolution_backward_weights_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *diff_weights_desc,
        const mkldnn_memory_desc_t *diff_bias_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);

/** Initializes a convolution descriptor @p conv_desc for backward propagation
 * with respect to weights using @p alg_kind, memory descriptors, @p strides,
 * @p dilates @p padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API
mkldnn_dilated_convolution_backward_weights_desc_init(
        mkldnn_convolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *diff_weights_desc,
        const mkldnn_memory_desc_t *diff_bias_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t dilates, const mkldnn_dims_t padding_l,
        const mkldnn_dims_t padding_r, mkldnn_padding_kind_t padding_kind);

/** @} */

/** @addtogroup c_api_deconvolution Deconvolution
 * A primitive to compute deconvolution using different algorithms.
 *
 * @{ */


/** Initializes a deconvolution descriptor @p deconv_desc for forward propagation
 * using @p prop_kind (possible values are #mkldnn_forward_training or
 * #mkldnn_forward_inference), @p alg_kind, memory descriptors, @p strides, @p
 * padding_l, @p padding_r, and @p padding_kind. In order to create a
 * deconvolution without bias, @p bias_desc should be either @c NULL or point to
 * a descriptor with memory format equals to #mkldnn_format_undef.
 *
 * @note if @p padding_r is @c NULL, the padding is supposed to be symmetric
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_deconvolution_forward_desc_init(
        mkldnn_deconvolution_desc_t *conv_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);

/** Initializes a deconvolution descriptor @p conv_desc for backward propagation
 * with respect to data using @p alg_kind, memory descriptors, @p strides, @p
 * padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_deconvolution_backward_data_desc_init(
        mkldnn_deconvolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);

/** Initializes a deconvolution descriptor @p conv_desc for backward propagation
 * with respect to weights using @p alg_kind, memory descriptors, @p strides,
 * @p padding_l, @p padding_r, and @p padding_kind.
 *
 * @note memory descriptors are allowed to be initialized with #mkldnn_any
 * value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_deconvolution_backward_weights_desc_init(
        mkldnn_deconvolution_desc_t *conv_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *diff_weights_desc,
        const mkldnn_memory_desc_t *diff_bias_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t padding_l, const mkldnn_dims_t padding_r,
        mkldnn_padding_kind_t padding_kind);
/** @} */

/** @addtogroup c_api_eltwise Eltwise
 * A primitive to compute element wise operations like parametric rectifier
 * linear unit (ReLU).
 *
 * Both forward and backward passes support in-place operation, i.e. src
 * and dst point to the same memory for forward, and diff_dst and diff_src
 * point to the same memory for backward pass.
 *
 * @warning Since for backward pass original src is required, in-place forward
 * pass in general cannot be applied during training. However for some kinds of
 * element wise operations (namely ReLU with alpha parameter equals 0) dst and
 * src can be interchangeable for the backward pass, which allows performing
 * in-place forward even for training.
 *
 * @{ */

/** Initializes a @p eltwise_desc for forward propagation using @p prop_kind
 * (possible values are #mkldnn_forward_training or #mkldnn_forward_inference),
 * @p alg_kind algorithm, memory descriptor @p data_desc, and @p alpha,
 * @p beta parameters.
 * @sa mkldnn_eltwise_desc_t for details */
mkldnn_status_t MKLDNN_API mkldnn_eltwise_forward_desc_init(
        mkldnn_eltwise_desc_t *eltwise_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *data_desc,
        float alpha, float beta);

/** Initializes a @p eltwise_desc for backward propagation using @p alg_kind
 * algorithm memory descriptors @p diff_data_desc and @p data_desc, and
 * @p alpha, @p beta parameters.
 * @sa mkldnn_eltwise_desc_t for details */
mkldnn_status_t MKLDNN_API mkldnn_eltwise_backward_desc_init(
        mkldnn_eltwise_desc_t *eltwise_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_data_desc,
        const mkldnn_memory_desc_t *data_desc, float alpha, float beta);

/** @} */

/** @addtogroup c_api_relu ReLU (deprecated, use Eltwise instead)
 * A primitive to compute a parametric rectifier linear unit (ReLU).
 *
 * \f[dst[n][c][h][w] = \max(src[n][c][h][w], 0) +
 *                      \min(src[n][c][h][w], 0) \cdot negative\_slope\f]
 * @{ */

/** Initializes a @p relu_desc for forward propagation using @p prop_kind
 * (possible values are #mkldnn_forward_training or #mkldnn_forward_inference),
 * @p negative_slope and memory descriptor @p data_desc.
 *
 * @deprecated use mkldnn_eltwise_forward_desc_init() instead, with @p alpha
 * equals @p negative_slope */
MKLDNN_DEPRECATED
mkldnn_status_t MKLDNN_API mkldnn_relu_forward_desc_init(
        mkldnn_relu_desc_t *relu_desc, mkldnn_prop_kind_t prop_kind,
        const mkldnn_memory_desc_t *data_desc, float negative_slope);

/** Initializes a @p relu_desc for backward propagation using @p negative_slope
 * and memory descriptors @p diff_data_desc and @p data_desc.
 *
 * @deprecated use mkldnn_eltwise_backward_desc_init() instead, with @p alpha
 * equals @p negative_slope */
MKLDNN_DEPRECATED
mkldnn_status_t MKLDNN_API mkldnn_relu_backward_desc_init(
        mkldnn_relu_desc_t *relu_desc,
        const mkldnn_memory_desc_t *diff_data_desc,
        const mkldnn_memory_desc_t *data_desc, float negative_slope);

/** @} */

/** @addtogroup c_api_softmax Softmax
 * A primitive to perform softmax.
 *
 * \f[dst[u][c][in] =
 *    \frac{\exp(src[ou][c][in]) - \max\limits_{c}(src[ou][c][in])}
 *    {\sum\limits_{c}\{\exp(src[ou][c][in]) 
 *    - \max\limits_{c}(src[ou][c][in])\}},\f]
 *
 * where \f$ou, iu\f$ are outer and inner sizes repectively, defined
 * by @p data_desc.dims and @p softmax_axis.
 * @{ */

/** Initializes a @p softmax_desc for forward propagation using @p prop_kind
 * (possible value are #mkldnn_forward_training or #mkldnn_forward_inference)
 * and memory descriptor @p data_desc. */
mkldnn_status_t MKLDNN_API mkldnn_softmax_forward_desc_init(
        mkldnn_softmax_desc_t *softmax_desc, mkldnn_prop_kind_t prop_kind,
        const mkldnn_memory_desc_t *data_desc, int softmax_axis);

/** Initializes a @p softmax_desc for backward propagation using memory
 * descriptors @p diff_desc and @p data_desc. */
mkldnn_status_t MKLDNN_API mkldnn_softmax_backward_desc_init(
        mkldnn_softmax_desc_t *softmax_desc,
        const mkldnn_memory_desc_t *diff_desc,
        const mkldnn_memory_desc_t *data_desc, int softmax_axis);

/** @} */

/** @addtogroup c_api_pooling Pooling
 * A primitive to perform max or average pooling.
 * 
 * Max pooling:
 * \f[dst[n][oc][oh][ow] =
 *     \max\limits_{kw,kh}
 *     (src[n][ic][oh \cdot s_h - p_l[0] + kh][ow \cdot s_w - p_r[1] + kw]),\f]
 *
 * Average pooling:
 * \f[dst[n][oc][oh][ow] =
 *     \frac{1}{KW \cdot KH}\sum\limits_{kw,kh}
 *     src[n][ic][oh \cdot s_h - p_l[0] + kh][ow \cdot s_w - p_r[1] + kw],\f]
 *
 * where \f$p_l, p_r\f$ are @p padding_l and @p padding_r
 * respectively and output spatial dimensions are calculated
 * similarly as done in convolution.
 * @{ */

/** Initializes a pooling descriptor @p pool_desc for forward propagation using
 * @p prop_kind (possible values are #mkldnn_forward_training or
 * #mkldnn_forward_inference), @p alg_kind, memory descriptors, and pooling
 * parameters in spatial domain: @p strides, @p kernel sizes, @p padding_l, @p
 * padding_r, and @p padding_kind.
 *
 * @note if @p padding_r is @c NULL, the padding is supposed to be symmetric
 *
 * @todo clarify! */
mkldnn_status_t MKLDNN_API mkldnn_pooling_forward_desc_init(
        mkldnn_pooling_desc_t *pool_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t kernel, const mkldnn_dims_t padding_l,
        const mkldnn_dims_t padding_r, mkldnn_padding_kind_t padding_kind);

/** Initializes a pooling descriptor @p pool_desc for backward propagation
 * using @p alg_kind, memory descriptors, and pooling parameters in spatial
 * domain: @p strides, @p kernel sizes, @p padding_l, @p padding_r, and @p
 * padding_kind.
 *
 * @todo clarify! */
mkldnn_status_t MKLDNN_API mkldnn_pooling_backward_desc_init(
        mkldnn_pooling_desc_t *pool_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_src_desc,
        const mkldnn_memory_desc_t *diff_dst_desc, const mkldnn_dims_t strides,
        const mkldnn_dims_t kernel, const mkldnn_dims_t padding_l,
        const mkldnn_dims_t padding_r, mkldnn_padding_kind_t padding_kind);

/** @} */

/** @addtogroup c_api_lrn LRN
 * A primitive to perform local response normalization (LRN) across or within
 * channels. 
 * 
 * LRN accross channels:
 * \f[dst[n][c][h][w] = \left\{k + \frac{\alpha}{n_{l}}
 *                      \sum\limits_{i=-(n_{l}-1)/2}^{(n_{l}+1)/2}
 *                      (src[n][c+i][h][w])^2\right\}^{-\beta}
 *                      src[n][c][h][w],\f]
 *
 * LRN within channels:
 * \f[dst[n][c][h][w] = \left\{k + \frac{\alpha}{n_{l}}
 *                      \sum\limits_{i=-(n_{l}-1)/2}^{(n_{l}+1)/2}
 *                      (src[n][c][h+i][w+i])^2\right\}^{-\beta}
 *                      src[n][c][h][w],\f]
 *
 * where \f$n_{l}\f$ is the @p local_size.
 * @{ */

/** Initializes an @p lrn_desc for forward propagation using @p prop_kind
 * (possible values are #mkldnn_forward_training or #mkldnn_forward_inference),
 * @p alg_kind, memory descriptor @p data_desc, and regularization
 * parameters @p local_size, @p alpha, @p beta, and @p k. */
mkldnn_status_t MKLDNN_API mkldnn_lrn_forward_desc_init(
        mkldnn_lrn_desc_t *lrn_desc, mkldnn_prop_kind_t prop_kind,
        mkldnn_alg_kind_t alg_kind, const mkldnn_memory_desc_t *data_desc,
        int local_size, float alpha, float beta, float k);

/** Initializes an @p lrn_desc for backward propagation using @p alg_kind,
 * memory descriptors @p data_desc, and @p diff_data_desc, and regularization
 * parameters @p local_size, @p alpha, @p beta, and @p k. */
mkldnn_status_t MKLDNN_API mkldnn_lrn_backward_desc_init(
        mkldnn_lrn_desc_t *lrn_desc, mkldnn_alg_kind_t alg_kind,
        const mkldnn_memory_desc_t *diff_data_desc,
        const mkldnn_memory_desc_t *data_desc, int local_size, float alpha,
        float beta, float k);

/** @} */

/** @addtogroup c_api_batch_normalization Batch Normalization
 * A primitive to perform batch normalization.
 *
 * \f[dst[n][c][h][w] = \gamma[c] \frac{src[n][c][h][w] - \mu[c]}
 *                      {\sqrt{\sigma[c] + eps}} + \beta[c],\f]
 *
 * where \f$\gamma[c], \beta[c]\f$ are weights and bias for a channel and,
 *
 * \f$\mu[c] = \frac{1}{NHW} \sum\limits_{whn} src[n][c][h][w]\f$,
 * \f$\sigma[c] = \frac{1}{NHW} \sum\limits_{whn}
 *                              (src[n][c][h][w] - \mu[c])^2\f$,
 *
 * and eps is a constant to improve numerical stability.
 *
 * Both forward and backward passes support in-place operation, i.e. src
 * and dst point to the same memory for forward, and diff_dst and diff_src
 * point to the same memory for backward pass.
 *
 * @{ */

/** Initializes a batch normalization descriptor @p bnrm_desc for forward
 * propagation using @p prop_kind, (possible values are
 * #mkldnn_forward_training or #mkldnn_forward_inference), memory descriptor
 * @p data_desc, normalization parameter @p epsilon and flags (possible values
 * are #mkldnn_use_global_stats and #mkldnn_use_scaleshift).
 *
 * @sa mkldnn_batch_normalization_desc_t */
mkldnn_status_t MKLDNN_API mkldnn_batch_normalization_forward_desc_init(
        mkldnn_batch_normalization_desc_t *bnrm_desc,
        mkldnn_prop_kind_t prop_kind, const mkldnn_memory_desc_t *data_desc,
        float epsilon, unsigned flags);

/** Initializes a batch normalization descriptor @p bnrm_desc for backward
 * propagation with respect to data and scale-shift parameters using memory
 * descriptors @p data_desc and @p diff_data_desc, and normalization parameter
 * @p epsilon and flags (possible values are #mkldnn_use_global_stats and
 * #mkldnn_use_scaleshift).
 *
 * @sa mkldnn_batch_normalization_desc_t */
mkldnn_status_t MKLDNN_API mkldnn_batch_normalization_backward_desc_init(
        mkldnn_batch_normalization_desc_t *bnrm_desc,
        mkldnn_prop_kind_t prop_kind,
        const mkldnn_memory_desc_t *diff_data_desc,
        const mkldnn_memory_desc_t *data_desc,
        float epsilon, unsigned flags);

/** @} */

/** @addtogroup c_api_inner_product Inner product
 * A primitive to compute an inner product.
 *
 * Inner product layer is also known as fully connected layer.
 * with spatial dimension:
 *
 * \f[dst[n][oc] = \sum\limits_{ic, kh, kw}
 *                 src[n][ic][kh][kw] \cdot weights[oc][ic][kh][kw]
 *                 + bias[oc]\f]
 * @{ */

/** Initializes an inner product descriptor @p ip_desc for forward propagation
 * using @p prop_kind (possible values are #mkldnn_forward_training or
 * #mkldnn_forward_inference) and memory descriptors. In order to create an
 * inner product without bias, @p bias_desc should be either @c NULL or a
 * pointer to descriptor with memory format equals to #mkldnn_format_undef.
 *
 * @note
 *     memory descriptors are allowed to be initialized with #mkldnn_any value
 *     of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_inner_product_forward_desc_init(
        mkldnn_inner_product_desc_t *ip_desc, mkldnn_prop_kind_t prop_kind,
        const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_desc);

/** Initializes an inner product descriptor @p ip_desc for backward propagation
 * with respect to data using memory descriptors.
 *
 * @note
 *     memory descriptors are allowed to be initialized with #mkldnn_any value
 *     of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_inner_product_backward_data_desc_init(
        mkldnn_inner_product_desc_t *ip_desc,
        const mkldnn_memory_desc_t *diff_src_desc,
        const mkldnn_memory_desc_t *weights_desc,
        const mkldnn_memory_desc_t *diff_dst_desc);

/** Initializes an inner product descriptor @p ip_desc for backward propagation
 * with respect to weights using memory descriptors.
 *
 * @note
 *     memory descriptors are allowed to be initialized with #mkldnn_any value
 *     of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_inner_product_backward_weights_desc_init(
        mkldnn_inner_product_desc_t *ip_desc,
        const mkldnn_memory_desc_t *src_desc,
        const mkldnn_memory_desc_t *diff_weights_desc,
        const mkldnn_memory_desc_t *diff_bias_desc,
        const mkldnn_memory_desc_t *diff_dst_desc);

/** @} */

/** @addtogroup c_api_convolution_relu Convolution followed by ReLU (deprecated)
 * A merged primitive to compute a convolution followed by relu.
 * @{ */

/** Initializes a merged convolution-relu descriptor @p conv_relu_desc for
 * forward propagation (supported inference mode only) using convolution
 * descriptor @p conv_desc and ReLU parameter @p negative slope.
 *
 * @deprecated use mkldnn_convolution_desc_init with
 * mkldnn_post_ops_append_eltwise to append ReLU */
mkldnn_status_t MKLDNN_API mkldnn_convolution_relu_desc_init(
        mkldnn_convolution_relu_desc_t *conv_relu_desc,
        const mkldnn_convolution_desc_t *conv_desc, float negative_slope);

/** @} */

/** @addtogroup c_api_rnn RNN
 * A primitive to compute common recurrent layer.
 * @todo add additional description for the group
 * @{ */

/**
 * Initializes a recurrent cell descriptor @p rnn_cell_desc
 * using @p rnn_cell_desc, @p kind (possible values are
 *  #mkldnn_vanilla_rnn, #mkldnn_vanilla_lstm, #mkldnn_vanilla_gru),
 *  @p f (possible values are #mkldnn_eltwise_relu,
 *   #mkldnn_eltwise_tanh), @p flags, @p alpha, and @p clipping.
 */
mkldnn_status_t MKLDNN_API mkldnn_rnn_cell_desc_init(
        mkldnn_rnn_cell_desc_t *rnn_cell_desc,
        mkldnn_alg_kind_t kind, mkldnn_alg_kind_t f,
        unsigned int flags, float alpha, float clipping);

/** Returns the number of gates of a particular @p rnn_cell_desc. */
int MKLDNN_API mkldnn_rnn_cell_get_gates_count(
        const mkldnn_rnn_cell_desc_t *rnn_cell_desc);

/** Returns the number of states of a particular @p rnn_cell_desc. */
int MKLDNN_API mkldnn_rnn_cell_get_states_count(
        const mkldnn_rnn_cell_desc_t *rnn_cell_desc);

/** Initializes a rnn descriptor @p rnn_desc for forward propagation
 * using @p prop_kind, @p rnn_cell_desc, @p direction, and memory descriptors.
 * @note if @p prop_kind equals #mkldnn_forward_training, you need to query a
 * worskpace memory descriptor before creating the primitive.
 *
 * @note all memory descriptors except @p src_iter_desc are allowed to be
 * initialized with #mkldnn_any value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_rnn_forward_desc_init(
        mkldnn_rnn_desc_t *rnn_desc, mkldnn_prop_kind_t prop_kind,
        const mkldnn_rnn_cell_desc_t *rnn_cell_desc,
        const mkldnn_rnn_direction_t direction,
        const mkldnn_memory_desc_t *src_layer_desc,
        const mkldnn_memory_desc_t *src_iter_desc,
        const mkldnn_memory_desc_t *weights_layer_desc,
        const mkldnn_memory_desc_t *weights_iter_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_layer_desc,
        const mkldnn_memory_desc_t *dst_iter_desc);

/** Initializes a rnn descriptor @p rnn_desc for backward propagation
 * using @p prop_kind, @p rnn_cell_desc, @p direction, and memory descriptors.
 * @note all memory descriptors are allowed to be initialized with
 * #mkldnn_any value of @p format_kind. */
mkldnn_status_t MKLDNN_API mkldnn_rnn_backward_desc_init(
        mkldnn_rnn_desc_t *rnn_desc, mkldnn_prop_kind_t prop_kind,
        const mkldnn_rnn_cell_desc_t *rnn_cell_desc,
        const mkldnn_rnn_direction_t direction,
        const mkldnn_memory_desc_t *src_layer_desc,
        const mkldnn_memory_desc_t *src_iter_desc,
        const mkldnn_memory_desc_t *weights_layer_desc,
        const mkldnn_memory_desc_t *weights_iter_desc,
        const mkldnn_memory_desc_t *bias_desc,
        const mkldnn_memory_desc_t *dst_layer_desc,
        const mkldnn_memory_desc_t *dst_iter_desc,
        const mkldnn_memory_desc_t *diff_src_layer_desc,
        const mkldnn_memory_desc_t *diff_src_iter_desc,
        const mkldnn_memory_desc_t *diff_weights_layer_desc,
        const mkldnn_memory_desc_t *diff_weights_iter_desc,
        const mkldnn_memory_desc_t *diff_bias_desc,
        const mkldnn_memory_desc_t *diff_dst_layer,
        const mkldnn_memory_desc_t *diff_dst_iter_desc);

/** @} */

/** @} */

/** @addtogroup c_api_engine Engine operations
 * @{ */

/** Returns the number of engines of a particular @p kind. */
size_t MKLDNN_API mkldnn_engine_get_count(mkldnn_engine_kind_t kind);

/** Creates an @p engine of particular @p kind and @p index. */
mkldnn_status_t MKLDNN_API mkldnn_engine_create(mkldnn_engine_t *engine,
        mkldnn_engine_kind_t kind, size_t index);

/** Returns the kind of an @p engine. */
mkldnn_status_t MKLDNN_API mkldnn_engine_get_kind(mkldnn_engine_t engine,
        mkldnn_engine_kind_t *kind);

/** Destroys an @p engine. */
mkldnn_status_t MKLDNN_API mkldnn_engine_destroy(mkldnn_engine_t engine);

/** @} */

/** @addtogroup c_api_stream Execution stream operations
 * @{ */

/** Creates an execution @p stream of @p stream_kind. */
mkldnn_status_t MKLDNN_API mkldnn_stream_create(mkldnn_stream_t *stream,
        mkldnn_stream_kind_t stream_kind);

/** Submits @p primitives to an execution @p stream. The number of primitives
 * is @p n.  All or none of the primitives can be lazy. In case of an error,
 * returns the offending @p error_primitive if it is not @c NULL. */
mkldnn_status_t MKLDNN_API mkldnn_stream_submit(mkldnn_stream_t stream,
        size_t n, mkldnn_primitive_t primitives[],
        mkldnn_primitive_t *error_primitive);

/** Waits for all primitives in the execution @p stream to finish. Returns
 * immediately if @p block is zero. In case of an error, returns
 * the offending @p error_primitive if it is not @c NULL. */
mkldnn_status_t MKLDNN_API mkldnn_stream_wait(mkldnn_stream_t stream,
        int block, mkldnn_primitive_t *error_primitive);

/** Reruns all the primitives within the @p stream. In case of an error,
 * returns the offending @p error_primitive if it is not @c NULL. */
mkldnn_status_t MKLDNN_API mkldnn_stream_rerun(mkldnn_stream_t stream,
        mkldnn_primitive_t *error_primitive);

/** Destroys an execution @p stream. */
mkldnn_status_t MKLDNN_API mkldnn_stream_destroy(mkldnn_stream_t stream);

/** @} */

/** @addtogroup c_api_service Service functions
 * @{ */

/** Sets verbosity level (print information to stdout).
 * Possible levels are:
 *  - 0 -- no verbose output
 *  - 1 -- primitive information at execution
 *  - 2 -- primitive information at creation and execution
 *
 * @note
 *     Dumping information might affect performance */
mkldnn_status_t MKLDNN_API mkldnn_verbose_set(int level);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
