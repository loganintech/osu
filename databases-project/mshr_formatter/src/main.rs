use std::env::args;
use std::fs::File;
use std::io::{BufRead, BufReader, BufWriter, Write};

use lazy_static::lazy_static;
use regex::Regex;

lazy_static! {
    static ref SPACES: Regex = Regex::new(" +").unwrap();
}
fn main() -> Result<(), Box<dyn std::error::Error>> {
    if let Some(filepath) = args().skip(1).take(1).next() {
        let mut inp = BufReader::new(File::open(filepath)?);
        process_file(&mut inp)?;
    }

    Ok(())
}

fn process_file(inp: &mut impl BufRead) -> Result<(), std::io::Error> {
    let mut out = BufWriter::new(File::create("processed_file.csv")?);
    let mut count: usize = 0;
    out.write_all(
        b"source_id,source,begin_date,end_date,station_status,ncdcstn_id,icao_id,wban_id,faa_id,nwsli_id,wmo_id,coop_id,transmittal_id,ghcnd_id,name_principal,name_principal_short,name_coop,name_coop_short,name_publication,name_alias,nws_clim_div,nws_clim_div_name,state_prov,county,nws_st_code,fips_country_code,fips_country_name,nws_region,nws_wfo,elev_ground,elev_ground_unit,elev_barom,elev_barom_unit,elev_air,elev_air_unit,elev_zerodat,elev_zerodat_unit,elev_unk,elev_unk_unit,lat_dec,lon_dec,lat_lon_precision,relocation,utc_offset,obs_env,platform,ghcnmlt_id,county_fips_code,datum_horizontal,datum_vertical,lat_lon_source,igra_id,hpd_id"
    )
    .unwrap();
    inp.lines()
        .filter_map(Result::ok)
        // .filter(|line| line.len() == 294)
        .for_each(|line: String| {
            if count % 1000 == 0 {
                println!("Processing line {}", count);
            }
            count += 1;

            let source_id = &line[0..20];
            let source = &line[22 - 1..31];
            let begin_date = &line[33 - 1..40];
            let end_date = &line[42 - 1..49];
            let station_status = &line[51 - 1..70];
            let ncdcstn_id = &line[72 - 1..91];
            let icao_id = &line[93 - 1..112];
            let wban_id = &line[114 - 1..133];
            let faa_id = &line[135 - 1..154];
            let nwsli_id = &line[156 - 1..175];
            let wmo_id = &line[177 - 1..196];
            let coop_id = &line[198 - 1..217];
            let transmittal_id = &line[219 - 1..238];
            let ghcnd_id = &line[240 - 1..259];
            let name_principal = &line[261 - 1..360];
            let name_principal_short = &line[362 - 1..391];
            let name_coop = &line[393 - 1..492];
            let name_coop_short = &line[494 - 1..523];
            let name_publication = &line[525 - 1..624];
            let name_alias = &line[626 - 1..725];
            let nws_clim_div = &line[727 - 1..736];
            let nws_clim_div_name = &line[738 - 1..777];
            let state_prov = &line[779 - 1..788];
            let county = &line[790 - 1..839];
            let nws_st_code = &line[841 - 1..842];
            let fips_country_code = &line[844 - 1..845];
            let fips_country_name = &line[847 - 1..946];
            let nws_region = &line[948 - 1..977];
            let nws_wfo = &line[979 - 1..988];
            let elev_ground = &line[990 - 1..1029];
            let elev_ground_unit = &line[1031 - 1..1050];
            let elev_barom = &line[1052 - 1..1091];
            let elev_barom_unit = &line[1093 - 1..1112];
            let elev_air = &line[1114 - 1..1153];
            let elev_air_unit = &line[1155 - 1..1174];
            let elev_zerodat = &line[1176 - 1..1215];
            let elev_zerodat_unit = &line[1217 - 1..1236];
            let elev_unk = &line[1238 - 1..1277];
            let elev_unk_unit = &line[1279 - 1..1298];
            let lat_dec = &line[1300 - 1..1319];
            let lon_dec = &line[1321 - 1..1340];
            let lat_lon_precision = &line[1342 - 1..1351];
            let relocation = &line[1353 - 1..1414];
            let utc_offset = &line[1416 - 1..1431];
            let obs_env = &line[1433 - 1..1472];
            let platform = &line[1474 - 1..1573];
            let ghcnmlt_id = &line[1575 - 1..1594];
            let county_fips_code = &line[1596 - 1..1600];
            let datum_horizontal = &line[1602 - 1..1631];
            let datum_vertical = &line[1633 - 1..1662];
            let lat_lon_source = &line[1664 - 1..1763];
            let igra_id = &line[1765 - 1..1784];
            let hpd_id = &line[1786 - 1..1805];

            let newline = [
                source_id,
                source,
                begin_date,
                end_date,
                station_status,
                ncdcstn_id,
                icao_id,
                wban_id,
                faa_id,
                nwsli_id,
                wmo_id,
                coop_id,
                transmittal_id,
                ghcnd_id,
                name_principal,
                name_principal_short,
                name_coop,
                name_coop_short,
                name_publication,
                name_alias,
                nws_clim_div,
                nws_clim_div_name,
                state_prov,
                county,
                nws_st_code,
                fips_country_code,
                fips_country_name,
                nws_region,
                nws_wfo,
                elev_ground,
                elev_ground_unit,
                elev_barom,
                elev_barom_unit,
                elev_air,
                elev_air_unit,
                elev_zerodat,
                elev_zerodat_unit,
                elev_unk,
                elev_unk_unit,
                lat_dec,
                lon_dec,
                lat_lon_precision,
                relocation,
                utc_offset,
                obs_env,
                platform,
                ghcnmlt_id,
                county_fips_code,
                datum_horizontal,
                datum_vertical,
                lat_lon_source,
                igra_id,
                hpd_id,
            ]
            .iter()
            .map(|part| part.trim().to_string())
            .collect::<Vec<String>>()
            .join(",");

            out.write_all(newline.as_bytes()).unwrap();
            out.write_all(b"\n").unwrap();
        });

    Ok(())
}
