/*
    This file is a part of SORT(Simple Open Ray Tracing), an open-source cross
    platform physically based renderer.

    Copyright (c) 2011-2020 by Jiayin Cao - All rights reserved.

    SORT is a free software written for educational purpose. Anyone can distribute
    or modify it under the the terms of the GNU General Public License Version 3 as
    published by the Free Software Foundation. However, there is NO warranty that
    all components are functional in a perfect manner. Without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include "imagetexture3d.h"

ImageTexture3D::ImageTexture3D(unsigned w, unsigned h, unsigned d, const float* data) {
    if (w == 0 || h == 0 || d == 0)
        return;

    unsigned offset = 0;
    m_memory->m_rgb = std::make_unique<Spectrum[]>(w * h * d);
    for (auto i = 0u; i < d; ++i) {
        for (auto j = 0u; j < h; ++j) {
            for (auto k = 0u; k < w; ++k) {
                m_memory->m_rgb[offset][0] = data[offset * 3];
                m_memory->m_rgb[offset][1] = data[offset * 3 + 1];
                m_memory->m_rgb[offset][2] = data[offset * 3 + 2];

                ++offset;
            }
        }
    }
}

Spectrum ImageTexture3D::Sample(int x, int y, int z) const {
    if (x < 0 || x >= (int)m_width || y < 0 || y >= (int)m_height || z < 0 || z >= (int)m_depth)
        return 0.0f;

    const auto offset = z * m_width * m_height + y * m_width + x;
    return m_memory->m_rgb[offset];
}

Spectrum ImageTexture3D::Sample(float u, float v, float w) const{
    // There should have been proper filtering algorithms
    // However, since this is mainly for medium density for now, there will be no filter supported.
    // If the uvw is out of range, just retuen 0.0.
    if (u < 0.0f || u >= 1.0f || v < 0.0f || v >= 1.0f || w < 0.0f || w >= 1.0f)
        return 0.0f;

    const auto x = (unsigned)(u * m_width);
    const auto y = (unsigned)(v * m_height);
    const auto z = (unsigned)(w * m_depth);
    const auto offset = z * m_width * m_height + y * m_width + x;
    return m_memory->m_rgb[offset];
}